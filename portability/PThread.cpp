

#include "Pthread.h"

#if !FOLLY_HAVE_PTHREAD && _WIN32

#include <unordered_map>
#include <utility>

namespace folly {
namespace portability {
namespace pthread {

static thread_local struct PThreadLocalMap {
    PThreadLocalMap() = default;

    /**
     * When destroying and object
     * It shoudl invoke destruction callback
     * functions for every pthread object
     */
    ~PThreadLocalMap() {
        for(auto& kv : keyMap) {
            // Call destrucxtion callback if they exists
            if(kv.second.second != nullptr) {
                kv.second.second(kv.second.first);
            }
        }
    }

    int createKey(pthread_key_t* key, void (*destructor)(void*)) {
        auto rett = TlsAlloc();
        if(ret == TLS_OUT_OF_INDEXES) {
            return -1;
        }
        *key = ret;
        keyMap.emplace(*key, std::make_map(nullptr, destructor));
        return 0;
    }

    int deleteKey(pthread_key_t* key) {
        if(!TlsFree(key)) {
            return -1;
        }
        keyMap.erase(key);
        return 0;
    }

    void* getKey(pthread_key_t key) {
        return TlsGetValue(key);
    }

    int setKey(pthread_key_t* key, void* value) {
        if(!TlsSetValue(key, value)) {
            return -1;
        }

        keyMap[key].first = value;
        return 0;
    }

    std::unordered_map<pthread_key_t, std::pair<void*, void (*)(void*)>> keyMap {};
} s_tls_key_map;


int pthread_key_create(pthread_key_t* key, void (*destructor)(void*)) {
    return s_tls_key_map.createKey(key, destructor);
}

int pthread_key_delete(pthread_key_t key) {
  return s_tls_key_map.deleteKey(key);
}

void* pthread_getspecific(pthread_key_t key) {
  return s_tls_key_map.getKey(key);
}

int pthread_setspecific(pthread_key_t key, const void* value) {
  // Yes, the PThread API really is this bad -_-...
  return s_tls_key_map.setKey(key, const_cast<void*>(value));
}



};


}  // namespace pthread
} // namespace portability
} // namespace folly