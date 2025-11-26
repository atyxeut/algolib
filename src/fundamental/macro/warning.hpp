#ifndef AAL_SRC_FUNDAMENTAL_MACRO_WARNING_HPP
#define AAL_SRC_FUNDAMENTAL_MACRO_WARNING_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/fundamental/macro/warning.hpp */

// clang-format off

#if defined(_MSC_VER)
  #define AAL_INT_WCONVERSION_WCOMPARE_PUSH __pragma(warning(push)) \
                                            __pragma(warning(disable: 4018)) \
                                            __pragma(warning(disable: 4267)) \
                                            __pragma(warning(disable: 4389))
  #define AAL_INT_WCONVERSION_WCOMPARE_POP __pragma(warning(pop))
#else // gcc or clang
  #define AAL_INT_WCONVERSION_WCOMPARE_PUSH _Pragma("GCC diagnostic push") \
                                            _Pragma("GCC diagnostic ignored \"-Wsign-conversion\"") \
                                            _Pragma("GCC diagnostic ignored \"-Wsign-compare\"") \
                                            _Pragma("GCC diagnostic ignored \"-Wshorten-64-to-32\"")
  #define AAL_INT_WCONVERSION_WCOMPARE_POP _Pragma("GCC diagnostic pop")
#endif // msvc

// clang-format on

#endif // AAL_SRC_FUNDAMENTAL_MACRO_WARNING_HPP
