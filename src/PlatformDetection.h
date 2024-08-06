
#ifdef _WIN32

#elif defined(__APPLE__) || defined(__MARCH__)
  #include <TargetConditionals.h>
  #if TARGET_OS_IPHONE == 1
    #define PLATFORM_IOS
    #error "IOS is not supported"
  #elif TARGET_OS_MAC == 1
    #define PLATFORM_MACOS
  #else
    #error "unknown Apple platform"
  #endif
#else
 #error "Unknown platform"

#endif

