#ifndef AAL_SRC_MACROS_CONSTEXPR_HPP
#define AAL_SRC_MACROS_CONSTEXPR_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros/constexpr.hpp */

#include "cpp_version_test.hpp"

#if AAL_CPP14
#define AAL_CONSTEXPR14 constexpr
#else
#define AAL_CONSTEXPR14
#endif // apply constexpr if compiled with C++14

#if AAL_CPP20
#define AAL_CONSTEXPR20 constexpr
#else
#define AAL_CONSTEXPR20
#endif // apply constexpr if compiled with C++20

#if AAL_CPP23
#define AAL_CONSTEXPR23 constexpr
#else
#define AAL_CONSTEXPR23
#endif // apply constexpr if compiled with C++23

#endif // AAL_SRC_MACROS_CONSTEXPR_HPP
