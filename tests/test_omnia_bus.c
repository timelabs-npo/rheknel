#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rheknel/omnia_bus.h"

#include "fixtures/omnia-dns-macos.h"

#ifndef OMNIA_FIXTURE_DIR
#define OMNIA_FIXTURE_DIR "tests/fixtures"
#endif

static int failures;
static unsigned int action_count;

#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition); \
        ++failures; \
    } \
} while (0)

static void count_action(RheaContext *ctx) {
    (void)ctx;
    ++action_count;
}

static FILE *open_binary_read(const char *path) {
#if defined(_MSC_VER)
    FILE *file = NULL;
    return fopen_s(&file, path, "rb") == 0 ? file : NULL;
#else
    return fopen(path, "rb");
#endif
}

static size_t load_fixture(const char *name, uint8_t *buffer, size_t capacity) {
    char path[1024];
    FILE *file;
    long length;
    int written = snprintf(path, sizeof(path), "%s/%s", OMNIA_FIXTURE_DIR, name);
    if (written < 0 || (size_t)written >= sizeof(path)) {
        return 0;
    }
    file = open_binary_read(path);
    if (file == NULL || fseek(file, 0, SEEK_END) != 0) {
        if (file != NULL) {
            (void)fclose(file);
        }
        return 0;
    }
    length = ftell(file);
    if (length <= 0 || (size_t)length > capacity || fseek(file, 0, SEEK_SET) != 0) {
        (void)fclose(file);
        return 0;
    }
    if (fread(buffer, 1, (size_t)length, file) != (size_t)length || fclose(file) != 0) {
        return 0;
    }
    return (size_t)length;
}

static void test_golden(void) {
    OmniaBusView view;
    OmniaBusDecision decision;
    OmniaBusRecord record;
    CHECK(omnia_bus_open(omnia_dns_macos, omnia_dns_macos_size, &view) == OMNIA_BUS_OK);
    CHECK(view.record_count == 4u);
    CHECK(view.string_count > 4u);
    CHECK(view.created_at == UINT64_C(1786665600));
    CHECK(view.fresh_until == UINT64_C(1789257600));
    CHECK(omnia_bus_record_at(&view, 0, &record) == OMNIA_BUS_OK);
    CHECK(record.id.size > 3u);
    CHECK(record.evidence_count == 1u);
    CHECK(record.provenance_count == 1u);
    CHECK(omnia_bus_evaluate(&view, view.created_at, &decision) == OMNIA_BUS_OK);
    CHECK(decision.verdict == RHEA_OK);
    CHECK(decision.applicable_records == 2u);
    CHECK(omnia_bus_evaluate(&view, view.fresh_until, &decision) == OMNIA_BUS_OK);
    CHECK(decision.verdict == RHEA_OK);
    CHECK(omnia_bus_evaluate(&view, view.fresh_until + 1u, &decision) == OMNIA_BUS_ERR_STALE);
    CHECK(decision.verdict == RHEA_ESCALATE);
    CHECK(omnia_bus_evaluate(&view, view.created_at - 1u, &decision) == OMNIA_BUS_ERR_NOT_YET_VALID);
    CHECK(decision.verdict == RHEA_ESCALATE);
}

static void test_negative_fixtures(void) {
    uint8_t buffer[8192];
    OmniaBusView view;
    size_t size;
    size = load_fixture("contradictory.omnb", buffer, sizeof(buffer));
    CHECK(size > 0u);
    CHECK(omnia_bus_open(buffer, size, &view) == OMNIA_BUS_ERR_CONTRADICTORY);
    size = load_fixture("provenance-missing.omnb", buffer, sizeof(buffer));
    CHECK(size > 0u);
    CHECK(omnia_bus_open(buffer, size, &view) == OMNIA_BUS_ERR_PROVENANCE_MISSING);
    size = load_fixture("unsupported-version.omnb", buffer, sizeof(buffer));
    CHECK(size > 0u);
    CHECK(omnia_bus_open(buffer, size, &view) == OMNIA_BUS_ERR_UNSUPPORTED_VERSION);
    size = load_fixture("malformed.omnb", buffer, sizeof(buffer));
    CHECK(size > 0u);
    CHECK(omnia_bus_open(buffer, size, &view) == OMNIA_BUS_ERR_HEADER);
    size = load_fixture("boundary.omnb", buffer, sizeof(buffer));
    CHECK(size > 0u);
    CHECK(omnia_bus_open(buffer, size, &view) == OMNIA_BUS_OK);
    CHECK(view.created_at == UINT64_MAX);
    CHECK(view.fresh_until == UINT64_MAX);
}

static void test_integrity(void) {
    uint8_t tampered[sizeof(omnia_dns_macos)];
    OmniaBusView view;
    memcpy(tampered, omnia_dns_macos, sizeof(tampered));
    tampered[sizeof(tampered) - 1u] ^= 1u;
    CHECK(omnia_bus_open(tampered, sizeof(tampered), &view) == OMNIA_BUS_ERR_HASH);
}

static void test_dispatch_gate(void) {
    OmniaJudgeInput input;
    OmniaBusDecision decision;
    RheaContext context;
    RheaVerdict verdict;
    input.data = omnia_dns_macos;
    input.size = omnia_dns_macos_size;
    input.now_epoch_s = UINT64_C(1786665600);
    input.decision = &decision;
    context.data = &input;
    context.data_size = sizeof(input);
    context.meta = NULL;
    context.status = 0;
    context.phase = "test";
    context.data_kind = RHEA_DATA_TYPED;
    action_count = 0;
    rhea_reset();
    CHECK(rhea_add_judge("omnia", rhea_omnia_judge));
    CHECK(rhea_on("commit", count_action));
    verdict = rhea_dispatch("omnia", "commit", &context);
    CHECK(verdict == RHEA_OK);
    CHECK(action_count == 1u);
    input.now_epoch_s = UINT64_C(1789257601);
    verdict = rhea_dispatch("omnia", "commit", &context);
    CHECK(verdict == RHEA_ESCALATE);
    CHECK(action_count == 1u);
    CHECK(rhea_emit("commit", &context) == RHEA_ERROR);
    CHECK(rhea_dispatch("missing", "commit", &context) == RHEA_ERROR);
    CHECK(action_count == 1u);
}

int main(void) {
    test_golden();
    test_negative_fixtures();
    test_integrity();
    test_dispatch_gate();
    if (failures != 0) {
        fprintf(stderr, "%d test assertion(s) failed\n", failures);
        return 1;
    }
    printf("omnia_bus: all adversarial and boundary checks passed\n");
    return 0;
}
