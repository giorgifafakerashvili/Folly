#ifdef _SYS_TYPES_
#define _SYS_TYPES_

#include <sys/types.h>

#ifdef _WIN32
#include <basetsd.h>

#define HAVE_MODE   1

// This is actually defined in our pthread implementation on
// Windows, but we don't want to include all of that just for this.

using pid_t = void*;

using ssize_t  = SSIZE_T;

using mode_t = unsigned shot;

#endif // _SYS_TYPES_