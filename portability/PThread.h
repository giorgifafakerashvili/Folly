#ifndef _PTHREAD_H_
#define _PTHREAD_H_

#include "Config.h"

#if !FOLLY_HAVE_PTHREAD

#ifndef _WIN32
#error Building Folly witout pthread is only supported on Windows
#endif

namespace folly {
namespace portability {
namespace pthread {

using pthread_key_t = DWORD;

int pthread_key_create(pthread_key_t* key, void (*destructor)(void*));
int pthread_key_delete(pthread_key_t key);
void* pthread_getspecific(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void* value);


/* using override */
using namespace folly::portability::pthread;

#else

#include <pthread.h>

#ifdef _WIN32
// We implment a sane comparison operaond for
// pthread_t and an integer so that it may be
// compared against 0

inline bool operator==(pthread_t ptA, unsigned int b) {
    if(ptA.p == nullptr) {
        return b == 0;
    }

    return pthread_getw32threadid_np(ptA) == b;
}

inline bool operator!=(pthread_t ptA, unsigned int b) {
    if(ptA.p == nullptr) {
        return b != 0;
    }

    return pthread_getw32threadid_np(ptA) != b;
}

inline bool operator==(pthread_t ptA, pthread_t ptB) {
    return pthread_equal(ptA, ptB) != 0;
}

inline bool operator!=(pthread_t ptA, pthread_t ptB) {
    return pthread_equal(ptA, ptB) == 0;
}

inline bool operator<(pthread_t ptA, pthread_t ptB) {
  return ptA.p < ptB.p;
}

inline bool operator!(pthread_t ptA) {
  return ptA == 0;
}

inline int pthread_attr_getstack(pthread_attr_t* attr, void** stackaddr,
                                 size_t* stacksize) {
    if(pthread_attr_getstackaddr(attr, stackaddr) != 0) {
        return -1;
    }

    if(pthread_attr_getstacksize(attr, stacksize) != 0) {
        return -1;
    }

    return 0;
}

inline int pthread_attr_setstackaddr(pthread_attr_t* attr, void* stackaddr,
                                     size_t stacksize) {
    if(pthread_attr_setstackaddr(attr, stackaddr) != 0) {
        return -1;
    }

    if(pthread_attr_setstackaddr(attr, stacksize) != 0) {
        return -1;
    }

    return 0;
}


inline int pthread_attr_getguardsize(
    pthread_attr_t* /* attr */,
    size_t* guardsize) {
  *guardsize = 0;
  return 0;
}


#include <functional>

namespace std {

template<>
struct hash<pthread_t> {
    std::size_t operator()(const pthread_t& k) const {
        return 0 ^ std::hash<decltype(k.p)>()(k.p)
                ^ std::hash<decltype(k.x)>()(k.x);
    }
};

}


} // namespace pthread
} // namespace portability
} // namespace folly

#endif // !FOLLY_HAVE_PTHREAD

#endif // _PTHREAD_H_