#ifndef _GFLAGS_H_
#define _GFLAGS_H_

#include "../portability/Config.h"

#if !FOLLY_HAVE_LIBFLAGS

#define DECLARE_VARIABLE() \
    static_assert(false, "You shouldn't be using GFLAGS internals");

#define FOLLY_DECLARE_FLAG(_type, _shortType, _name) \
    namespace fL##_shortType {                       \
        extern _type FLAGS_##_name;                   \
    }                                                \
    using fl##_shortType::FLAGS_##_name

#define DECLARE_bool(_name) FOLLY_DECLARE_FLAG(bool, B, _name)
#define DECLARE_double(_name) FOLLY_DECLARE_FLAG(double, D, _name)
#define DECLARE_int32(_name) FOLLY_DECLARE_FLAG(int, I, _name)
#define DECLARE_int64(_name) FOLLY_DECLARE_FLAG(long long, I64, _name)
#define DECLARE_uint64(_name) FOLLY_DECLARE_FLAG(unsigned long long, U64, _name)
#define DECLARE_string(_name) FOLLY_DECLARE_FLAG(std::string, S, _name)

#define FOLLY_DEFINE_FLAG(_type, _shortType, _name, _default)   \
    namespace fl##_shortType {                                  \
        _type FLAGS_##_name = _default;                         \
    }                                                           \
    using fl##_shortType::FLAGS_##_name

#define DEFINE_bool(_name, _default, _description) \
  FOLLY_DEFINE_FLAG(bool, B, _name, _default)
#define DEFINE_double(_name, _default, _description) \
  FOLLY_DEFINE_FLAG(double, D, _name, _default)
#define DEFINE_int32(_name, _default, _description) \
  FOLLY_DEFINE_FLAG(int, I, _name, _default)
#define DEFINE_int64(_name, _default, _description) \
  FOLLY_DEFINE_FLAG(long long, I64, _name, _default)
#define DEFINE_uint64(_name, _default, _description) \
  FOLLY_DEFINE_FLAG(unsigned long long, U64, _name, _default)
#define DEFINE_string(_name, _default, _description) \
  FOLLY_DEFINE_FLAG(std::string, S, _name, _default)

namespace google {
class FlagSaver {};
}

#else
#include <gflags/gflags.h>
#endif // !FOLLY_HAVE_LIBFLAGS

#endif // _GFLAGS_H_