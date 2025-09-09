#ifndef AAL_SRC_MACROS_HPP
#define AAL_SRC_MACROS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros.hpp */

#if defined(__i386__) || defined(_M_IX86)
#define AAL_ARCH_X86 1
#endif // x86

#if defined(__x86_64__) || defined(_M_X64)
#define AAL_ARCH_X86_64 1
#endif // x86_64

#ifdef _MSC_VER
#define AAL_MSVC 1
#endif // MSVC

#if __cplusplus >= 201402L
#define AAL_CPP14 1
#endif // C++14

#if __cplusplus >= 201703L
#define AAL_CPP17 1
#endif // C++17

#if __cplusplus >= 202002L
#define AAL_CPP20 1
#endif // C++20

#if __cplusplus >= 202302L
#define AAL_CPP23 1
#endif // C++23

#if AAL_CPP14
#define AAL_CONSTEXPR14 constexpr
#else
#define AAL_CONSTEXPR14
#endif // C++14

#if AAL_CPP20
#define AAL_CONSTEXPR20 constexpr
#else
#define AAL_CONSTEXPR20
#endif // C++20

#if AAL_CPP23
#define AAL_CONSTEXPR23 constexpr
#else
#define AAL_CONSTEXPR23
#endif // C++23

#if AAL_CPP20
#include <version>

#if __cpp_lib_format >= 201907L
#define AAL_CPP20_FORMAT 1
#endif // C++20 <format>

#if __cpp_lib_print >= 202207L
#define AAL_CPP23_PRINT 1
#endif // C++23 <print>
#endif // C++20

#endif // AAL_SRC_MACROS_HPP
