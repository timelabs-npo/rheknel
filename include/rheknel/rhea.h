#ifndef RHEKNEL_RHEA_H
#define RHEKNEL_RHEA_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RHEA_MAX_TAGS 8
#define RHEA_MAX_CALLBACKS 8
#define RHEA_MAX_TAG_LEN 32

typedef enum {
    RHEA_OK = 0,
    RHEA_REJECT = 1,
    RHEA_ESCALATE = 2,
    RHEA_ERROR = 3
} RheaVerdict;

typedef enum {
    RHEA_DATA_NONE = 0,
    RHEA_DATA_TYPED = 1,
    RHEA_DATA_TEXT = 2
} RheaDataKind;

typedef struct {
    const void *data;
    size_t data_size;
    void *meta;
    int status;
    const char *phase;
    RheaDataKind data_kind;
} RheaContext;

typedef void (*ActionFunc)(RheaContext *ctx);
typedef RheaVerdict (*JudgeFunc)(RheaContext *ctx);

bool rhea_on(const char *tag, ActionFunc callback);
bool rhea_add_judge(const char *tag, JudgeFunc callback);
RheaVerdict rhea_judge(const char *tag, RheaContext *ctx);
RheaVerdict rhea_dispatch(const char *judge_tag, const char *action_tag, RheaContext *ctx);

/* Retained for source compatibility; direct unmediated emission always fails closed. */
RheaVerdict rhea_emit(const char *tag, RheaContext *ctx);

/* Deterministically clears the fixed-capacity registries. */
void rhea_reset(void);

#ifdef __cplusplus
}
#endif

#endif
