#include "rheknel/rhea.h"

#include <string.h>

typedef struct {
    char tag[RHEA_MAX_TAG_LEN];
    ActionFunc callbacks[RHEA_MAX_CALLBACKS];
    unsigned int count;
} ActionRegistry;

typedef struct {
    char tag[RHEA_MAX_TAG_LEN];
    JudgeFunc callbacks[RHEA_MAX_CALLBACKS];
    unsigned int count;
} JudgeRegistry;

static ActionRegistry actions[RHEA_MAX_TAGS];
static JudgeRegistry judges[RHEA_MAX_TAGS];
static unsigned int action_tags_count;
static unsigned int judge_tags_count;

static bool valid_tag(const char *tag) {
    size_t length;
    if (tag == NULL || tag[0] == '\0') {
        return false;
    }
    length = strlen(tag);
    return length < RHEA_MAX_TAG_LEN;
}

static int find_action(const char *tag) {
    unsigned int index;
    if (!valid_tag(tag)) {
        return -1;
    }
    for (index = 0; index < action_tags_count; ++index) {
        if (strcmp(actions[index].tag, tag) == 0) {
            return (int)index;
        }
    }
    return -1;
}

static int find_judge(const char *tag) {
    unsigned int index;
    if (!valid_tag(tag)) {
        return -1;
    }
    for (index = 0; index < judge_tags_count; ++index) {
        if (strcmp(judges[index].tag, tag) == 0) {
            return (int)index;
        }
    }
    return -1;
}

void rhea_reset(void) {
    memset(actions, 0, sizeof(actions));
    memset(judges, 0, sizeof(judges));
    action_tags_count = 0;
    judge_tags_count = 0;
}

bool rhea_on(const char *tag, ActionFunc callback) {
    int index;
    if (!valid_tag(tag) || callback == NULL) {
        return false;
    }
    index = find_action(tag);
    if (index < 0) {
        if (action_tags_count >= RHEA_MAX_TAGS) {
            return false;
        }
        index = (int)action_tags_count++;
        (void)strcpy(actions[index].tag, tag);
    }
    if (actions[index].count >= RHEA_MAX_CALLBACKS) {
        return false;
    }
    actions[index].callbacks[actions[index].count++] = callback;
    return true;
}

bool rhea_add_judge(const char *tag, JudgeFunc callback) {
    int index;
    if (!valid_tag(tag) || callback == NULL) {
        return false;
    }
    index = find_judge(tag);
    if (index < 0) {
        if (judge_tags_count >= RHEA_MAX_TAGS) {
            return false;
        }
        index = (int)judge_tags_count++;
        (void)strcpy(judges[index].tag, tag);
    }
    if (judges[index].count >= RHEA_MAX_CALLBACKS) {
        return false;
    }
    judges[index].callbacks[judges[index].count++] = callback;
    return true;
}

RheaVerdict rhea_judge(const char *tag, RheaContext *ctx) {
    int index;
    unsigned int callback_index;
    if (ctx == NULL) {
        return RHEA_ERROR;
    }
    index = find_judge(tag);
    if (index < 0 || judges[index].count == 0) {
        return RHEA_ERROR;
    }
    for (callback_index = 0; callback_index < judges[index].count; ++callback_index) {
        RheaVerdict verdict = judges[index].callbacks[callback_index](ctx);
        if (verdict < RHEA_OK || verdict > RHEA_ERROR) {
            return RHEA_ERROR;
        }
        if (verdict != RHEA_OK) {
            return verdict;
        }
    }
    return RHEA_OK;
}

static RheaVerdict emit_authorized(const char *tag, RheaContext *ctx) {
    int index;
    unsigned int callback_index;
    if (ctx == NULL || ctx->data_kind != RHEA_DATA_TYPED) {
        return RHEA_ERROR;
    }
    index = find_action(tag);
    if (index < 0 || actions[index].count == 0) {
        return RHEA_ERROR;
    }
    for (callback_index = 0; callback_index < actions[index].count; ++callback_index) {
        actions[index].callbacks[callback_index](ctx);
    }
    return RHEA_OK;
}

RheaVerdict rhea_emit(const char *tag, RheaContext *ctx) {
    (void)tag;
    (void)ctx;
    return RHEA_ERROR;
}

RheaVerdict rhea_dispatch(const char *judge_tag, const char *action_tag, RheaContext *ctx) {
    RheaVerdict verdict;
    if (ctx == NULL || ctx->data_kind != RHEA_DATA_TYPED) {
        return RHEA_ERROR;
    }
    verdict = rhea_judge(judge_tag, ctx);
    if (verdict != RHEA_OK) {
        return verdict;
    }
    return emit_authorized(action_tag, ctx);
}
