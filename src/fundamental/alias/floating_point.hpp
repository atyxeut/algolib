#ifndef AAL_SRC_FUNDAMENTAL_ALIAS_FLOATING_POINT_HPP
#define AAL_SRC_FUNDAMENTAL_ALIAS_FLOATING_POINT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/fundamental/alias/floating_point.hpp */

#include <type_traits>

// precision (significant digits)
// f32: 6 to 9
// f64: 15 to 17
// f80: 18 to 20
// f128: 33 to 35

using f32 = float;
using f64 = double;
using f80 = long double;

// clang-format off

// f128 is provided by compiler extensions (there is no f128 for MSVC), and is not supported by standard type traits
// for convenience, we consider that f128 only works on x86 or x86_64
#if defined(_MSC_VER) || (!defined(__i386__) && !defined(__x86_64__))
  using f128 = void;
#else // gcc or clang + x86(_64)
  // detail: https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html
  __extension__ using f128 = __float128;
#endif // msvc or not x86(_64)

using fmx = std::conditional_t<std::is_same_v<f128, void>, f80, f128>;

// clang-format on

#endif // AAL_SRC_FUNDAMENTAL_ALIAS_FLOATING_POINT_HPP
