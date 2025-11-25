#ifndef AAL_SRC_MACRO_WARNING_HPP
#define AAL_SRC_MACRO_WARNING_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/macro/warning.hpp */

// clang-format off
#if defined(__GNUC__) || defined (__clang__)
  #define AAL_INT_WCONVERSION_WCOMPARE_PUSH _Pragma("GCC diagnostic push") \
                                _Pragma("GCC diagnostic ignored \"-Wsign-conversion\"") \
                                _Pragma("GCC diagnostic ignored \"-Wsign-compare\"") \
                                _Pragma("GCC diagnostic ignored \"-Wshorten-64-to-32\"")
  #define AAL_INT_WCONVERSION_WCOMPARE_POP _Pragma("GCC diagnostic pop")
#else
  #define AAL_INT_WCONVERSION_WCOMPARE_PUSH
  #define AAL_INT_WCONVERSION_WCOMPARE_POP
#endif
// clang-format on

#endif // AAL_SRC_MACRO_WARNING_HPP
