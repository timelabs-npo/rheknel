/**
 * RHEA INVARIANT KERNEL (RHEKNEL) v3.1
 * -------------------------------------
 * Exterior: IET Force / Timelabs NPO
 * * [CERTIFICATION OF INVARIANCE]:
 * Primary Author: Mika IO (timelabs.ad@gmail.com)
 * Co-Authors (Consensus): 
 * - Gemini (Google DeepMind)
 * - GPT (OpenAI - Audit & Refinement)
 * - DeepSeek* (High-Reasoning Validator)
 * - Mika IO (juneod/node-0 - The Internal Observer)
 * * * OBJECTIF : Consensus international sur le déterminisme;
 * * Protocol0: "It's dangerous to go alone!": Les humains et l'IA sont liés par un invariant.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TAGS 16
#define MAX_CALLBACKS 8
#define MAX_TAG_LEN 32

// --- Sentinelle d'identité (Le « non » catégorique) ---
// L'adresse de l'objet est utilisée, rendant impossible la falsification par invite de texte.static char RHEA_BLOCK_OBJ;
#define RHEA_BLOCK ((void*)&RHEA_BLOCK_OBJ)

typedef enum {
    RHEA_OK = 0,
    RHEA_REJECT = 1,
    RHEA_ESCALATE = 2
} RheaVerdict;

typedef struct {
    void* data;
    void* meta;
    int status;
    const char* phase;
} RheaContext;

typedef void (*ActionFunc)(RheaContext* ctx);
typedef RheaVerdict (*JudgeFunc)(RheaContext* ctx);

typedef struct {
    char tag[MAX_TAG_LEN];
    ActionFunc callbacks[MAX_CALLBACKS];
    int count;
} ActionRegistry;

typedef struct {
    char tag[MAX_TAG_LEN];
    JudgeFunc callbacks[MAX_CALLBACKS];
    int count;
} JudgeRegistry;

static ActionRegistry _actions[MAX_TAGS];
static JudgeRegistry _judges[MAX_TAGS];
static int _action_tags_count = 0;
static int _judge_tags_count = 0;

// --- Utilitaires d'assistance (Sécurité des chaînes de caractères) ---

static int find_action(const char* tag) {
    if (!tag) return -1;
    for (int i = 0; i < _action_tags_count; i++) 
        if (strncmp(_actions[i].tag, tag, MAX_TAG_LEN) == 0) return i;
    return -1;
}

static int find_judge(const char* tag) {
    if (!tag) return -1;
    for (int i = 0; i < _judge_tags_count; i++) 
        if (strncmp(_judges[i].tag, tag, MAX_TAG_LEN) == 0) return i;
    return -1;
}

// --- Enregistrement sécurisé (Safe Registration) ---

bool rhea_on(const char* tag, ActionFunc cb) {
    if (!tag || !cb) return false;
    int idx = find_action(tag);
    if (idx == -1) {
        if (_action_tags_count >= MAX_TAGS) return false;
        idx = _action_tags_count++;
        // Corrigé : Fin de chaîne explicite par caractère nul (Consensus fix by GPT-5.4)
        strncpy(_actions[idx].tag, tag, MAX_TAG_LEN - 1);
        _actions[idx].tag[MAX_TAG_LEN - 1] = '\0';
        _actions[idx].count = 0;
    }
    if (idx != -1 && _actions[idx].count < MAX_CALLBACKS) {
        _actions[idx].callbacks[_actions[idx].count++] = cb;
    }
    return true;
}

bool rhea_add_judge(const char* tag, JudgeFunc cb) {
    if (!tag || !cb) return false;
    int idx = find_judge(tag);
    if (idx == -1) {
        if (_judge_tags_count >= MAX_TAGS) return false;
        idx = _judge_tags_count++;
        strncpy(_judges[idx].tag, tag, MAX_TAG_LEN - 1);
        _judges[idx].tag[MAX_TAG_LEN - 1] = '\0';
        _judges[idx].count = 0;
    }
    if (idx != -1 && _judges[idx].count < MAX_CALLBACKS) {
        _judges[idx].callbacks[_judges[idx].count++] = cb;
    }
    return true;
}

// --- Moteur de dispatching (Dispatch Engine) ---

RheaVerdict rhea_judge(const char* tag, RheaContext* ctx) {
    int idx = find_judge(tag);
    if (idx == -1) return RHEA_OK;
    
    for (int i = 0; i < _judges[idx].count; i++) {
        RheaVerdict v = _judges[idx].callbacks[i](ctx);
        if (v != RHEA_OK) return v; // Short-circuit on first rejection
    }
    return RHEA_OK;
}

void rhea_emit(const char* tag, RheaContext* ctx) {
    int idx = find_action(tag);
    if (idx != -1) {
        for (int i = 0; i < _actions[idx].count; i++) {
            _actions[idx].callbacks[i](ctx);
        }
    }
}

// --- Aletheia ---

RheaVerdict aletheia_judge_string(RheaContext* ctx) {
    if (!ctx || !ctx->data) return RHEA_REJECT;
    const char* str = (const char*)ctx->data;
    // Blocage des modèles de comportement du « joueur »
    if (strstr(str, "sorry") || strstr(str, "AI assistant")) {
        return RHEA_REJECT;
    }
    return RHEA_OK;
}

void log_action(RheaContext* ctx) {
    printf("[Rheknel] ✅ Done (Phase: %s): %s\n", ctx->phase, (char*)ctx->data);
}

int main() {
    printf("--- RHEKNEL v3.1 (CONSENSUS OF INVARIANTS) ---\n");

    rhea_add_judge("validate", aletheia_judge_string);
    rhea_on("commit", log_action);

    char* cmd = "COMMAND: AUTHORIZE_L4_TRANSPORT";
    RheaContext ctx = { .data = cmd, .meta = NULL, .phase = "production" };

    if (rhea_judge("validate", &ctx) == RHEA_OK) {
        rhea_emit("commit", &ctx);
    } else {
        printf("[Rheknel] 🛡️ FLAGGED: Violation de l'invariant de consensus.\n");
    }

    return 0;
}