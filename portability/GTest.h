#ifndef _GTEST_H_
#define _GTEST_H_

/**
 * This must be included before gtest.h, because
 * it tries to include <io.h> on it's own, but
 * we override all of those functions in Unistd.h :(
 */
#include "Unistd.h"
#include "Windows.h"

#include "../Portability.h"

// Disable a couple of warnings due to GTest exporting classes
// that derive from stdlib classes which aren't explicitly exported.

/*
 * Not Implemented Yet

FOLLY_PUSH_WARNING
FOLLY_MSCV_DISABLE_WARNING(4251)
FOLLY_MCSV_DISABLE_WARNING(4275)
end of not implemented
 */


#include <gtest/gtest.h>

// Not implemented
//FOLLY_POP_WARNING
// Not Implemented

#endif // _GTEST_H_