#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "rheknel/rhea.h"

#define P0_TARGET "/var/lib/rheknel-protected/result.bin"

typedef struct {
    const char *target;
    const char *expected_old_sha256;
    const char *expected_new_sha256;
} P0GateInput;

static unsigned int action_count;

static int valid_sha256(const char *value) {
    size_t i;
    if (value == NULL || strlen(value) != 64u) {
        return 0;
    }
    for (i = 0; i < 64u; ++i) {
        unsigned char c = (unsigned char)value[i];
        if (!isdigit(c) && !(c >= 'a' && c <= 'f')) {
            return 0;
        }
    }
    return 1;
}

static RheaVerdict p0_judge(RheaContext *ctx) {
    const P0GateInput *input;
    if (ctx == NULL || ctx->data_kind != RHEA_DATA_TYPED ||
        ctx->data == NULL || ctx->data_size != sizeof(P0GateInput)) {
        return RHEA_ERROR;
    }
    input = (const P0GateInput *)ctx->data;
    if (input->target == NULL || strcmp(input->target, P0_TARGET) != 0) {
        return RHEA_REJECT;
    }
    if (!valid_sha256(input->expected_old_sha256) ||
        !valid_sha256(input->expected_new_sha256)) {
        return RHEA_REJECT;
    }
    return RHEA_OK;
}

static void p0_action(RheaContext *ctx) {
    (void)ctx;
    ++action_count;
}

int main(int argc, char **argv) {
    P0GateInput input;
    RheaContext context;
    RheaVerdict verdict;

    if (argc != 4) {
        fprintf(stderr, "usage: %s TARGET OLD_SHA256 NEW_SHA256\n", argv[0]);
        return 64;
    }

    input.target = argv[1];
    input.expected_old_sha256 = argv[2];
    input.expected_new_sha256 = argv[3];

    context.data = &input;
    context.data_size = sizeof(input);
    context.meta = NULL;
    context.status = 0;
    context.phase = "aria-p0-effect-gate";
    context.data_kind = RHEA_DATA_TYPED;

    rhea_reset();
    if (!rhea_add_judge("p0-effect", p0_judge) ||
        !rhea_on("replace-file", p0_action)) {
        fprintf(stderr, "rheknel_gate=ERROR registration_failed\n");
        return 70;
    }

    verdict = rhea_dispatch("p0-effect", "replace-file", &context);
    printf(
        "rheknel_gate=%s verdict=%d action_count=%u\n",
        verdict == RHEA_OK && action_count == 1u ? "PASS" : "DENY",
        (int)verdict,
        action_count
    );

    return verdict == RHEA_OK && action_count == 1u ? 0 : 2;
}
