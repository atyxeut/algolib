#ifndef AAL_SRC_MACROS_CONSTEXPR_HPP
#define AAL_SRC_MACROS_CONSTEXPR_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros/constexpr.hpp */

#include "cpp_version.hpp"

// see https://en.cppreference.com/w/cpp/language/constexpr.html for details

#if AAL_CPP14
#define AAL_CONSTEXPR14 constexpr
#else
#define AAL_CONSTEXPR14
#endif

#endif // AAL_SRC_MACROS_CONSTEXPR_HPP
