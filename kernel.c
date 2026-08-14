#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "rheknel/omnia_bus.h"
#include "rheknel/platform.h"

static unsigned int action_count;

static FILE *open_binary_read(const char *path) {
#if defined(_MSC_VER)
    FILE *file = NULL;
    return fopen_s(&file, path, "rb") == 0 ? file : NULL;
#else
    return fopen(path, "rb");
#endif
}

static void accepted_action(RheaContext *ctx) {
    (void)ctx;
    ++action_count;
}

static uint8_t *read_file(const char *path, size_t *size) {
    FILE *file;
    long length;
    uint8_t *buffer;
    if (rhea_platform_enter_readonly() != 0) {
        return NULL;
    }
    file = open_binary_read(path);
    if (file == NULL || fseek(file, 0, SEEK_END) != 0) {
        if (file != NULL) {
            (void)fclose(file);
        }
        return NULL;
    }
    length = ftell(file);
    if (length <= 0 || (unsigned long)length > OMNIA_BUS_MAX_SIZE || fseek(file, 0, SEEK_SET) != 0) {
        (void)fclose(file);
        return NULL;
    }
    buffer = (uint8_t *)malloc((size_t)length);
    if (buffer == NULL) {
        (void)fclose(file);
        return NULL;
    }
    if (fread(buffer, 1, (size_t)length, file) != (size_t)length) {
        (void)fclose(file);
        free(buffer);
        return NULL;
    }
    if (fclose(file) != 0) {
        free(buffer);
        return NULL;
    }
    if (rhea_platform_lock_stdio() != 0) {
        free(buffer);
        return NULL;
    }
    *size = (size_t)length;
    return buffer;
}

int main(int argc, char **argv) {
    uint64_t now_epoch_s;
    char *end = NULL;
    size_t size = 0;
    uint8_t *data;
    OmniaBusDecision decision;
    OmniaJudgeInput input;
    RheaContext context;
    RheaVerdict verdict;
    if (argc != 3) {
        fprintf(stderr, "usage: %s BUNDLE.omnb NOW_EPOCH_SECONDS\n", argv[0]);
        return 64;
    }
    errno = 0;
    now_epoch_s = (uint64_t)strtoull(argv[2], &end, 10);
    if (errno != 0 || end == argv[2] || *end != '\0') {
        fprintf(stderr, "invalid epoch seconds: %s\n", argv[2]);
        return 64;
    }
    data = read_file(argv[1], &size);
    if (data == NULL) {
        fprintf(stderr, "cannot read bundle: %s\n", argv[1]);
        return 66;
    }
    input.data = data;
    input.size = size;
    input.now_epoch_s = now_epoch_s;
    input.decision = &decision;
    context.data = &input;
    context.data_size = sizeof(input);
    context.meta = NULL;
    context.status = 0;
    context.phase = "omnia-bus-v1";
    context.data_kind = RHEA_DATA_TYPED;
    rhea_reset();
    if (!rhea_add_judge("omnia", rhea_omnia_judge) || !rhea_on("commit", accepted_action)) {
        free(data);
        return 70;
    }
    verdict = rhea_dispatch("omnia", "commit", &context);
    printf(
        "status=%s verdict=%d records_applicable=%u action_count=%u now=%" PRIu64 "\n",
        omnia_bus_status_string(decision.status),
        (int)verdict,
        (unsigned int)decision.applicable_records,
        action_count,
        now_epoch_s
    );
    free(data);
    return verdict == RHEA_OK ? 0 : 2;
}
