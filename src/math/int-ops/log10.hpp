#ifndef AAL_SRC_MATH_INT_OPS_LOG10_HPP
#define AAL_SRC_MATH_INT_OPS_LOG10_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/log10.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type-traits/integral.hpp"
#include <cassert>

namespace aal {

template <typename T>
AAL_CONSTEXPR14 auto ilog10(T x) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, int>::type
{
  assert(x >= 0 && "argument must be nonnegative");
  return x == 0 ? -1 : 0;
}

template <typename T>
AAL_CONSTEXPR14 auto digit_width(T x) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, int>::type
{
  assert(x >= 0 && "argument must be nonnegative");
  return x == 0 ? 1 : ilog10(x) + 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_LOG10_HPP
