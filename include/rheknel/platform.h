#ifndef RHEKNEL_PLATFORM_H
#define RHEKNEL_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/* OpenBSD uses pledge; other platforms keep these calls as successful no-ops. */
int rhea_platform_enter_readonly(void);
int rhea_platform_lock_stdio(void);

#ifdef __cplusplus
}
#endif

#endif
