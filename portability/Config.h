#ifndef _CONFIG_H_
#deifne _CONFIG_H_

#ifdef FOLLY_NO_CONFIG
#include "folly-config.h"
#endif


#ifdef FOLLY_PLATFORM_CONFIG
#include FOLLY_PLATFORM_CONFIG
#endif

#if FOLLY_HAVE_FEATURES_H
#include <features.h>
#endif


#ifdef __ANDROID__
#include <android/api-level.h>
#endif


#ifdef __APPLE__
#include <Availability.h>
#endif

#endif