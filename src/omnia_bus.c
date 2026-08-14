#include "rheknel/omnia_bus.h"

#include <string.h>

#include "sha256.h"

#define OMNIA_FLAGS 0x00000003u
#define OMNIA_FRAME_DIGEST_OFFSET 84u
#define OMNIA_FRAME_DIGEST_SIZE 32u

static uint16_t read_be16(const uint8_t *data) {
    return (uint16_t)(((uint16_t)data[0] << 8) | (uint16_t)data[1]);
}

static uint32_t read_be32(const uint8_t *data) {
    return ((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) | ((uint32_t)data[2] << 8) | (uint32_t)data[3];
}

static uint64_t read_be64(const uint8_t *data) {
    return ((uint64_t)read_be32(data) << 32) | (uint64_t)read_be32(data + 4);
}

static int bytes_are_zero(const uint8_t *data, size_t size) {
    size_t index;
    uint8_t value = 0;
    for (index = 0; index < size; ++index) {
        value = (uint8_t)(value | data[index]);
    }
    return value == 0;
}

static int bytes_equal(const uint8_t *left, const uint8_t *right, size_t size) {
    size_t index;
    uint8_t difference = 0;
    for (index = 0; index < size; ++index) {
        difference = (uint8_t)(difference | (uint8_t)(left[index] ^ right[index]));
    }
    return difference == 0;
}

static OmniaBusStatus read_uleb(
    const uint8_t *data,
    size_t limit,
    size_t *offset,
    uint64_t *value
) {
    uint64_t result = 0;
    unsigned int shift = 0;
    unsigned int count;
    uint8_t byte = 0;
    if (data == NULL || offset == NULL || value == NULL) {
        return OMNIA_BUS_ERR_ARGUMENT;
    }
    for (count = 0; count < 10u; ++count) {
        if (*offset >= limit) {
            return OMNIA_BUS_ERR_ULEB;
        }
        byte = data[(*offset)++];
        if (shift == 63u && (byte & 0xfeu) != 0) {
            return OMNIA_BUS_ERR_ULEB;
        }
        result |= (uint64_t)(byte & 0x7fu) << shift;
        if ((byte & 0x80u) == 0) {
            if (count > 0u && byte == 0u) {
                return OMNIA_BUS_ERR_ULEB;
            }
            *value = result;
            return OMNIA_BUS_OK;
        }
        shift += 7u;
    }
    return OMNIA_BUS_ERR_ULEB;
}

static int valid_utf8(const uint8_t *data, size_t size) {
    size_t index = 0;
    while (index < size) {
        uint8_t first = data[index++];
        uint32_t codepoint;
        unsigned int continuation;
        unsigned int count;
        if (first == 0u) {
            return 0;
        }
        if (first < 0x80u) {
            continue;
        }
        if (first >= 0xc2u && first <= 0xdfu) {
            codepoint = first & 0x1fu;
            continuation = 1;
        } else if (first >= 0xe0u && first <= 0xefu) {
            codepoint = first & 0x0fu;
            continuation = 2;
        } else if (first >= 0xf0u && first <= 0xf4u) {
            codepoint = first & 0x07u;
            continuation = 3;
        } else {
            return 0;
        }
        if (continuation > size - index) {
            return 0;
        }
        for (count = 0; count < continuation; ++count) {
            uint8_t next = data[index++];
            if ((next & 0xc0u) != 0x80u) {
                return 0;
            }
            codepoint = (codepoint << 6) | (uint32_t)(next & 0x3fu);
        }
        if ((continuation == 2u && codepoint < 0x800u) ||
            (continuation == 3u && codepoint < 0x10000u) ||
            codepoint > 0x10ffffu ||
            (codepoint >= 0xd800u && codepoint <= 0xdfffu)) {
            return 0;
        }
    }
    return 1;
}

static int slice_compare(OmniaBusSlice left, OmniaBusSlice right) {
    size_t common = left.size < right.size ? left.size : right.size;
    int compared = memcmp(left.data, right.data, common);
    if (compared != 0) {
        return compared;
    }
    if (left.size < right.size) {
        return -1;
    }
    if (left.size > right.size) {
        return 1;
    }
    return 0;
}

static int ascii_lower_hex(uint8_t value) {
    return (value >= (uint8_t)'0' && value <= (uint8_t)'9') ||
        (value >= (uint8_t)'a' && value <= (uint8_t)'f');
}

static int valid_evidence_id(OmniaBusSlice value) {
    size_t index;
    if (value.size != 71u || memcmp(value.data, "sha256:", 7) != 0) {
        return 0;
    }
    for (index = 7; index < value.size; ++index) {
        if (!ascii_lower_hex(value.data[index])) {
            return 0;
        }
    }
    return 1;
}

static int valid_provenance_id(OmniaBusSlice value, OmniaBusSlice source_path) {
    size_t index;
    size_t at = 0;
    size_t colon;
    int slash_seen = 0;
    if (value.size < 4u + 1u + 1u + 40u + 1u + source_path.size || memcmp(value.data, "git:", 4) != 0) {
        return 0;
    }
    for (index = 4; index < value.size; ++index) {
        if (value.data[index] == (uint8_t)'/' && at == 0u) {
            slash_seen = 1;
        }
        if (value.data[index] == (uint8_t)'@') {
            at = index;
            break;
        }
    }
    if (!slash_seen || at <= 5u || at + 41u >= value.size) {
        return 0;
    }
    for (index = at + 1u; index < at + 41u; ++index) {
        if (!ascii_lower_hex(value.data[index])) {
            return 0;
        }
    }
    colon = at + 41u;
    if (value.data[colon] != (uint8_t)':' || value.size - colon - 1u != source_path.size) {
        return 0;
    }
    return memcmp(value.data + colon + 1u, source_path.data, source_path.size) == 0;
}

OmniaBusStatus omnia_bus_get_string(const OmniaBusView *view, uint32_t string_id, OmniaBusSlice *slice) {
    size_t cursor;
    uint32_t index;
    if (view == NULL || slice == NULL || view->data == NULL || string_id >= view->string_count) {
        return OMNIA_BUS_ERR_ARGUMENT;
    }
    cursor = view->strings_offset;
    for (index = 0; index < view->string_count; ++index) {
        uint64_t length;
        OmniaBusStatus status = read_uleb(view->data, view->records_offset, &cursor, &length);
        if (status != OMNIA_BUS_OK || length > (uint64_t)(view->records_offset - cursor)) {
            return OMNIA_BUS_ERR_BOUNDS;
        }
        if (index == string_id) {
            slice->data = view->data + cursor;
            slice->size = (size_t)length;
            return OMNIA_BUS_OK;
        }
        cursor += (size_t)length;
    }
    return OMNIA_BUS_ERR_BOUNDS;
}

static OmniaBusStatus validate_state_word(uint16_t state_word) {
    unsigned int consistency = state_word & 0x3u;
    unsigned int applicability = (state_word >> 2) & 0x3u;
    unsigned int verifiability = (state_word >> 4) & 0x3u;
    unsigned int reliability = (state_word >> 6) & 0x7u;
    if ((state_word & 0xfe00u) != 0u || consistency > 3u || applicability > 3u ||
        verifiability > 3u || reliability > 4u) {
        return OMNIA_BUS_ERR_STATE;
    }
    return OMNIA_BUS_OK;
}

static OmniaBusStatus parse_metadata_value(
    const OmniaBusView *view,
    size_t *offset,
    size_t limit,
    unsigned int depth
) {
    uint8_t tag;
    uint64_t value;
    OmniaBusStatus status;
    if (depth > OMNIA_BUS_MAX_DEPTH || *offset >= limit) {
        return OMNIA_BUS_ERR_METADATA;
    }
    tag = view->data[(*offset)++];
    if (tag <= 2u) {
        return OMNIA_BUS_OK;
    }
    if (tag == 3u || tag == 4u) {
        status = read_uleb(view->data, limit, offset, &value);
        return status == OMNIA_BUS_OK ? OMNIA_BUS_OK : OMNIA_BUS_ERR_METADATA;
    }
    if (tag == 5u) {
        status = read_uleb(view->data, limit, offset, &value);
        if (status != OMNIA_BUS_OK || value >= view->string_count) {
            return OMNIA_BUS_ERR_METADATA;
        }
        return OMNIA_BUS_OK;
    }
    if (tag == 6u) {
        uint64_t index;
        status = read_uleb(view->data, limit, offset, &value);
        if (status != OMNIA_BUS_OK || value > (uint64_t)(limit - *offset)) {
            return OMNIA_BUS_ERR_METADATA;
        }
        for (index = 0; index < value; ++index) {
            status = parse_metadata_value(view, offset, limit, depth + 1u);
            if (status != OMNIA_BUS_OK) {
                return status;
            }
        }
        return OMNIA_BUS_OK;
    }
    if (tag == 7u) {
        uint64_t index;
        uint64_t previous_string_id = 0;
        status = read_uleb(view->data, limit, offset, &value);
        if (status != OMNIA_BUS_OK || value > (uint64_t)(limit - *offset)) {
            return OMNIA_BUS_ERR_METADATA;
        }
        for (index = 0; index < value; ++index) {
            uint64_t string_id;
            status = read_uleb(view->data, limit, offset, &string_id);
            if (status != OMNIA_BUS_OK || string_id >= view->string_count ||
                (index > 0u && string_id <= previous_string_id)) {
                return OMNIA_BUS_ERR_METADATA;
            }
            previous_string_id = string_id;
            status = parse_metadata_value(view, offset, limit, depth + 1u);
            if (status != OMNIA_BUS_OK) {
                return status;
            }
        }
        return OMNIA_BUS_OK;
    }
    return OMNIA_BUS_ERR_METADATA;
}

static OmniaBusStatus parse_record(
    const OmniaBusView *view,
    size_t *cursor,
    OmniaBusRecord *record
) {
    uint64_t body_size;
    uint64_t string_id;
    uint64_t count;
    uint64_t metadata_size;
    size_t body;
    size_t end;
    size_t metadata_offset;
    uint64_t index;
    uint64_t previous_string_id;
    OmniaBusStatus status;
    if (view == NULL || cursor == NULL || record == NULL) {
        return OMNIA_BUS_ERR_ARGUMENT;
    }
    status = read_uleb(view->data, view->size, cursor, &body_size);
    if (status != OMNIA_BUS_OK || body_size > (uint64_t)(view->size - *cursor)) {
        return OMNIA_BUS_ERR_RECORD;
    }
    body = *cursor;
    end = body + (size_t)body_size;
    if (end - body < 3u) {
        return OMNIA_BUS_ERR_RECORD;
    }
    if (view->data[body] != OMNIA_BUS_KIND_INVARIANT && view->data[body] != OMNIA_BUS_KIND_CHECK) {
        return OMNIA_BUS_ERR_RECORD;
    }
    record->kind = (OmniaBusKind)view->data[body++];
    record->state_word = read_be16(view->data + body);
    body += 2;
    status = validate_state_word(record->state_word);
    if (status != OMNIA_BUS_OK) {
        return status;
    }
    status = read_uleb(view->data, end, &body, &string_id);
    if (status != OMNIA_BUS_OK || string_id >= view->string_count ||
        omnia_bus_get_string(view, (uint32_t)string_id, &record->id) != OMNIA_BUS_OK || record->id.size == 0u) {
        return OMNIA_BUS_ERR_RECORD;
    }
    record->id_string_id = (uint32_t)string_id;
    status = read_uleb(view->data, end, &body, &string_id);
    if (status != OMNIA_BUS_OK || string_id >= view->string_count ||
        omnia_bus_get_string(view, (uint32_t)string_id, &record->source_path) != OMNIA_BUS_OK || record->source_path.size == 0u) {
        return OMNIA_BUS_ERR_RECORD;
    }
    record->source_path_string_id = (uint32_t)string_id;
    status = read_uleb(view->data, end, &body, &record->assessed_at);
    if (status != OMNIA_BUS_OK) {
        return OMNIA_BUS_ERR_RECORD;
    }
    status = read_uleb(view->data, end, &body, &record->fresh_until);
    if (status != OMNIA_BUS_OK || record->assessed_at > view->created_at || record->fresh_until < record->assessed_at) {
        return OMNIA_BUS_ERR_RECORD;
    }
    status = read_uleb(view->data, end, &body, &count);
    if (status != OMNIA_BUS_OK || count == 0u) {
        return OMNIA_BUS_ERR_EVIDENCE_MISSING;
    }
    record->evidence_count = count;
    previous_string_id = 0;
    for (index = 0; index < count; ++index) {
        OmniaBusSlice evidence;
        status = read_uleb(view->data, end, &body, &string_id);
        if (status != OMNIA_BUS_OK || string_id >= view->string_count ||
            (index > 0u && string_id <= previous_string_id) ||
            omnia_bus_get_string(view, (uint32_t)string_id, &evidence) != OMNIA_BUS_OK ||
            !valid_evidence_id(evidence)) {
            return OMNIA_BUS_ERR_EVIDENCE_MISSING;
        }
        previous_string_id = string_id;
    }
    status = read_uleb(view->data, end, &body, &count);
    if (status != OMNIA_BUS_OK || count == 0u) {
        return OMNIA_BUS_ERR_PROVENANCE_MISSING;
    }
    record->provenance_count = count;
    previous_string_id = 0;
    for (index = 0; index < count; ++index) {
        OmniaBusSlice provenance;
        status = read_uleb(view->data, end, &body, &string_id);
        if (status != OMNIA_BUS_OK || string_id >= view->string_count ||
            (index > 0u && string_id <= previous_string_id) ||
            omnia_bus_get_string(view, (uint32_t)string_id, &provenance) != OMNIA_BUS_OK ||
            !valid_provenance_id(provenance, record->source_path)) {
            return OMNIA_BUS_ERR_PROVENANCE_MISSING;
        }
        previous_string_id = string_id;
    }
    status = read_uleb(view->data, end, &body, &metadata_size);
    if (status != OMNIA_BUS_OK || metadata_size == 0u || metadata_size > (uint64_t)(end - body)) {
        return OMNIA_BUS_ERR_METADATA;
    }
    metadata_offset = body;
    status = parse_metadata_value(view, &metadata_offset, body + (size_t)metadata_size, 0);
    if (status != OMNIA_BUS_OK || metadata_offset != body + (size_t)metadata_size || metadata_offset != end) {
        return OMNIA_BUS_ERR_METADATA;
    }
    record->metadata.data = view->data + body;
    record->metadata.size = (size_t)metadata_size;
    *cursor = end;
    return OMNIA_BUS_OK;
}

OmniaBusStatus omnia_bus_record_at(const OmniaBusView *view, uint16_t index, OmniaBusRecord *record) {
    size_t cursor;
    uint16_t current;
    OmniaBusStatus status;
    if (view == NULL || record == NULL || index >= view->record_count) {
        return OMNIA_BUS_ERR_ARGUMENT;
    }
    cursor = view->records_offset;
    for (current = 0; current <= index; ++current) {
        status = parse_record(view, &cursor, record);
        if (status != OMNIA_BUS_OK) {
            return status;
        }
    }
    return OMNIA_BUS_OK;
}

OmniaBusStatus omnia_bus_open(const uint8_t *data, size_t size, OmniaBusView *view) {
    uint32_t total_size;
    uint32_t flags;
    uint32_t records_size;
    uint8_t calculated_digest[32];
    uint8_t zero_digest[32] = {0};
    RheaSha256 sha256;
    size_t cursor;
    uint32_t index;
    OmniaBusSlice previous_string = {NULL, 0};
    uint32_t previous_record_id = 0;
    if (data == NULL || view == NULL) {
        return OMNIA_BUS_ERR_ARGUMENT;
    }
    memset(view, 0, sizeof(*view));
    if (size < OMNIA_BUS_HEADER_SIZE || size > OMNIA_BUS_MAX_SIZE) {
        return OMNIA_BUS_ERR_SIZE;
    }
    if (memcmp(data, "OMNA", 4) != 0) {
        return OMNIA_BUS_ERR_MAGIC;
    }
    if (data[4] != OMNIA_BUS_ABI_MAJOR || data[5] != OMNIA_BUS_ABI_MINOR) {
        return OMNIA_BUS_ERR_UNSUPPORTED_VERSION;
    }
    if (read_be16(data + 6) != OMNIA_BUS_HEADER_SIZE) {
        return OMNIA_BUS_ERR_HEADER;
    }
    total_size = read_be32(data + 8);
    flags = read_be32(data + 12);
    if (total_size != size || flags != OMNIA_FLAGS || !bytes_are_zero(data + 16, 4) ||
        !bytes_are_zero(data + 124, 4) || bytes_are_zero(data + 52, 32)) {
        return OMNIA_BUS_ERR_HEADER;
    }
    view->data = data;
    view->size = size;
    view->record_count = read_be16(data + 20);
    view->string_count = read_be16(data + 22);
    view->strings_offset = read_be32(data + 24);
    view->records_offset = read_be32(data + 28);
    records_size = read_be32(data + 32);
    view->created_at = read_be64(data + 36);
    view->fresh_until = read_be64(data + 44);
    view->bundle_id_sid = read_be32(data + 116);
    view->target_sid = read_be32(data + 120);
    if (view->record_count == 0u || view->record_count > OMNIA_BUS_MAX_RECORDS || view->string_count == 0u ||
        view->strings_offset != OMNIA_BUS_HEADER_SIZE || view->records_offset < view->strings_offset ||
        view->records_offset > size || records_size != size - view->records_offset ||
        view->fresh_until < view->created_at || view->bundle_id_sid >= view->string_count ||
        view->target_sid >= view->string_count) {
        return OMNIA_BUS_ERR_BOUNDS;
    }
    rhea_sha256_init(&sha256);
    rhea_sha256_update(&sha256, data, OMNIA_FRAME_DIGEST_OFFSET);
    rhea_sha256_update(&sha256, zero_digest, sizeof(zero_digest));
    rhea_sha256_update(
        &sha256,
        data + OMNIA_FRAME_DIGEST_OFFSET + OMNIA_FRAME_DIGEST_SIZE,
        size - OMNIA_FRAME_DIGEST_OFFSET - OMNIA_FRAME_DIGEST_SIZE
    );
    rhea_sha256_final(&sha256, calculated_digest);
    if (!bytes_equal(calculated_digest, data + OMNIA_FRAME_DIGEST_OFFSET, sizeof(calculated_digest))) {
        return OMNIA_BUS_ERR_HASH;
    }
    cursor = view->strings_offset;
    for (index = 0; index < view->string_count; ++index) {
        uint64_t length;
        OmniaBusSlice current;
        OmniaBusStatus status = read_uleb(data, view->records_offset, &cursor, &length);
        if (status != OMNIA_BUS_OK || length > (uint64_t)(view->records_offset - cursor)) {
            return OMNIA_BUS_ERR_BOUNDS;
        }
        current.data = data + cursor;
        current.size = (size_t)length;
        if (!valid_utf8(current.data, current.size)) {
            return OMNIA_BUS_ERR_UTF8;
        }
        if (previous_string.data != NULL && slice_compare(previous_string, current) >= 0) {
            return OMNIA_BUS_ERR_STRING_ORDER;
        }
        previous_string = current;
        cursor += current.size;
    }
    if (cursor != view->records_offset) {
        return OMNIA_BUS_ERR_BOUNDS;
    }
    {
        OmniaBusSlice bundle_id;
        OmniaBusSlice target;
        if (omnia_bus_get_string(view, view->bundle_id_sid, &bundle_id) != OMNIA_BUS_OK || bundle_id.size == 0u ||
            omnia_bus_get_string(view, view->target_sid, &target) != OMNIA_BUS_OK || target.size == 0u) {
            return OMNIA_BUS_ERR_HEADER;
        }
    }
    cursor = view->records_offset;
    for (index = 0; index < view->record_count; ++index) {
        OmniaBusRecord record;
        OmniaBusStatus status = parse_record(view, &cursor, &record);
        if (status != OMNIA_BUS_OK) {
            return status;
        }
        if (index > 0u && record.id_string_id <= previous_record_id) {
            return OMNIA_BUS_ERR_CONTRADICTORY;
        }
        previous_record_id = record.id_string_id;
    }
    if (cursor != size) {
        return OMNIA_BUS_ERR_BOUNDS;
    }
    return OMNIA_BUS_OK;
}

static unsigned int verdict_rank(RheaVerdict verdict) {
    if (verdict == RHEA_ERROR) {
        return 3u;
    }
    if (verdict == RHEA_REJECT) {
        return 2u;
    }
    if (verdict == RHEA_ESCALATE) {
        return 1u;
    }
    return 0u;
}

static void merge_decision(
    OmniaBusDecision *decision,
    OmniaBusStatus status,
    RheaVerdict verdict,
    uint16_t record_index
) {
    if (verdict_rank(verdict) > verdict_rank(decision->verdict)) {
        decision->status = status;
        decision->verdict = verdict;
        decision->record_index = record_index;
    }
}

OmniaBusStatus omnia_bus_evaluate(const OmniaBusView *view, uint64_t now_epoch_s, OmniaBusDecision *decision) {
    uint16_t index;
    size_t cursor;
    if (view == NULL || decision == NULL || view->data == NULL) {
        return OMNIA_BUS_ERR_ARGUMENT;
    }
    decision->status = OMNIA_BUS_OK;
    decision->verdict = RHEA_OK;
    decision->record_index = UINT16_MAX;
    decision->applicable_records = 0;
    if (now_epoch_s < view->created_at) {
        merge_decision(decision, OMNIA_BUS_ERR_NOT_YET_VALID, RHEA_ESCALATE, UINT16_MAX);
    } else if (now_epoch_s > view->fresh_until) {
        merge_decision(decision, OMNIA_BUS_ERR_STALE, RHEA_ESCALATE, UINT16_MAX);
    }
    cursor = view->records_offset;
    for (index = 0; index < view->record_count; ++index) {
        OmniaBusRecord record;
        unsigned int consistency;
        unsigned int applicability;
        unsigned int verifiability;
        unsigned int reliability;
        OmniaBusStatus status = parse_record(view, &cursor, &record);
        if (status != OMNIA_BUS_OK) {
            merge_decision(decision, status, RHEA_ERROR, index);
            continue;
        }
        if (now_epoch_s < record.assessed_at) {
            merge_decision(decision, OMNIA_BUS_ERR_NOT_YET_VALID, RHEA_ESCALATE, index);
        } else if (now_epoch_s > record.fresh_until) {
            merge_decision(decision, OMNIA_BUS_ERR_STALE, RHEA_ESCALATE, index);
        }
        consistency = record.state_word & 0x3u;
        applicability = (record.state_word >> 2) & 0x3u;
        verifiability = (record.state_word >> 4) & 0x3u;
        reliability = (record.state_word >> 6) & 0x7u;
        if (consistency == 3u || applicability == 3u || verifiability == 3u || reliability == 4u) {
            merge_decision(decision, OMNIA_BUS_ERR_STATE, RHEA_ERROR, index);
        }
        if (consistency == 2u || verifiability == 2u || reliability == 3u) {
            merge_decision(decision, OMNIA_BUS_REJECTED, RHEA_REJECT, index);
        }
        if (consistency == 0u || applicability == 0u || verifiability == 0u || reliability == 0u || reliability == 2u) {
            merge_decision(decision, OMNIA_BUS_ERR_INSUFFICIENT, RHEA_ESCALATE, index);
        }
        if (applicability == 1u) {
            ++decision->applicable_records;
        }
    }
    if (decision->applicable_records == 0u) {
        merge_decision(decision, OMNIA_BUS_ERR_INSUFFICIENT, RHEA_ESCALATE, UINT16_MAX);
    }
    return decision->status;
}

RheaVerdict rhea_omnia_judge(RheaContext *ctx) {
    const OmniaJudgeInput *input;
    OmniaBusView view;
    OmniaBusDecision local_decision;
    OmniaBusDecision *decision;
    OmniaBusStatus status;
    if (ctx == NULL || ctx->data_kind != RHEA_DATA_TYPED || ctx->data == NULL ||
        ctx->data_size != sizeof(OmniaJudgeInput)) {
        return RHEA_ERROR;
    }
    input = (const OmniaJudgeInput *)ctx->data;
    decision = input->decision != NULL ? input->decision : &local_decision;
    status = omnia_bus_open(input->data, input->size, &view);
    if (status != OMNIA_BUS_OK) {
        decision->status = status;
        decision->record_index = UINT16_MAX;
        decision->applicable_records = 0;
        if (status == OMNIA_BUS_ERR_CONTRADICTORY) {
            decision->verdict = RHEA_REJECT;
        } else {
            decision->verdict = RHEA_ERROR;
        }
        return decision->verdict;
    }
    (void)omnia_bus_evaluate(&view, input->now_epoch_s, decision);
    return decision->verdict;
}

const char *omnia_bus_status_string(OmniaBusStatus status) {
    static const char *const names[] = {
        "OK", "ARGUMENT", "SIZE", "MAGIC", "UNSUPPORTED_VERSION", "HEADER", "BOUNDS", "HASH",
        "UTF8", "ULEB", "STRING_ORDER", "RECORD", "STATE", "METADATA", "EVIDENCE_MISSING",
        "PROVENANCE_MISSING", "CONTRADICTORY", "NOT_YET_VALID", "STALE", "INSUFFICIENT", "REJECTED"
    };
    if ((unsigned int)status >= sizeof(names) / sizeof(names[0])) {
        return "UNKNOWN_STATUS";
    }
    return names[(unsigned int)status];
}
