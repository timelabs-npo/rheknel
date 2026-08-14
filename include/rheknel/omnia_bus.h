#ifndef RHEKNEL_OMNIA_BUS_H
#define RHEKNEL_OMNIA_BUS_H

#include <stddef.h>
#include <stdint.h>

#include "rheknel/rhea.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OMNIA_BUS_ABI_MAJOR 1u
#define OMNIA_BUS_ABI_MINOR 0u
#define OMNIA_BUS_HEADER_SIZE 128u
#define OMNIA_BUS_MAX_SIZE (16u * 1024u * 1024u)
#define OMNIA_BUS_MAX_RECORDS 4096u
#define OMNIA_BUS_MAX_DEPTH 64u

typedef enum {
    OMNIA_BUS_OK = 0,
    OMNIA_BUS_ERR_ARGUMENT,
    OMNIA_BUS_ERR_SIZE,
    OMNIA_BUS_ERR_MAGIC,
    OMNIA_BUS_ERR_UNSUPPORTED_VERSION,
    OMNIA_BUS_ERR_HEADER,
    OMNIA_BUS_ERR_BOUNDS,
    OMNIA_BUS_ERR_HASH,
    OMNIA_BUS_ERR_UTF8,
    OMNIA_BUS_ERR_ULEB,
    OMNIA_BUS_ERR_STRING_ORDER,
    OMNIA_BUS_ERR_RECORD,
    OMNIA_BUS_ERR_STATE,
    OMNIA_BUS_ERR_METADATA,
    OMNIA_BUS_ERR_EVIDENCE_MISSING,
    OMNIA_BUS_ERR_PROVENANCE_MISSING,
    OMNIA_BUS_ERR_CONTRADICTORY,
    OMNIA_BUS_ERR_NOT_YET_VALID,
    OMNIA_BUS_ERR_STALE,
    OMNIA_BUS_ERR_INSUFFICIENT,
    OMNIA_BUS_REJECTED
} OmniaBusStatus;

typedef enum {
    OMNIA_BUS_KIND_INVARIANT = 1,
    OMNIA_BUS_KIND_CHECK = 2
} OmniaBusKind;

typedef struct {
    const uint8_t *data;
    size_t size;
} OmniaBusSlice;

typedef struct {
    const uint8_t *data;
    size_t size;
    uint16_t record_count;
    uint16_t string_count;
    uint32_t strings_offset;
    uint32_t records_offset;
    uint64_t created_at;
    uint64_t fresh_until;
    uint32_t bundle_id_sid;
    uint32_t target_sid;
} OmniaBusView;

typedef struct {
    OmniaBusKind kind;
    uint16_t state_word;
    uint64_t assessed_at;
    uint64_t fresh_until;
    uint64_t evidence_count;
    uint64_t provenance_count;
    uint32_t id_string_id;
    uint32_t source_path_string_id;
    OmniaBusSlice id;
    OmniaBusSlice source_path;
    OmniaBusSlice metadata;
} OmniaBusRecord;

typedef struct {
    OmniaBusStatus status;
    RheaVerdict verdict;
    uint16_t record_index;
    uint16_t applicable_records;
} OmniaBusDecision;

typedef struct {
    const uint8_t *data;
    size_t size;
    uint64_t now_epoch_s;
    OmniaBusDecision *decision;
} OmniaJudgeInput;

OmniaBusStatus omnia_bus_open(const uint8_t *data, size_t size, OmniaBusView *view);
OmniaBusStatus omnia_bus_get_string(const OmniaBusView *view, uint32_t string_id, OmniaBusSlice *slice);
OmniaBusStatus omnia_bus_record_at(const OmniaBusView *view, uint16_t index, OmniaBusRecord *record);
OmniaBusStatus omnia_bus_evaluate(const OmniaBusView *view, uint64_t now_epoch_s, OmniaBusDecision *decision);
RheaVerdict rhea_omnia_judge(RheaContext *ctx);
const char *omnia_bus_status_string(OmniaBusStatus status);

#ifdef __cplusplus
}
#endif

#endif
