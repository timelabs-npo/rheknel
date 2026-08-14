#include "rheknel/platform.h"

#if defined(__OpenBSD__)
#include <unistd.h>
#endif

int rhea_platform_enter_readonly(void) {
#if defined(__OpenBSD__)
    return pledge("stdio rpath", (const char *)0);
#else
    return 0;
#endif
}

int rhea_platform_lock_stdio(void) {
#if defined(__OpenBSD__)
    return pledge("stdio", (const char *)0);
#else
    return 0;
#endif
}
