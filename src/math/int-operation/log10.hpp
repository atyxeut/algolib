#ifndef AAL_SRC_MATH_INT_OPERATION_LOG10_HPP
#define AAL_SRC_MATH_INT_OPERATION_LOG10_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-operation/log10.hpp */

#include <cassert>

#include "../../type-trait/integral.hpp"

namespace aal {

template <typename T>
auto ilog10(T x) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, int>::type
{
  assert(x >= 0 && "argument must be nonnegative");
  return x == 0 ? -1 : 0;
}

template <typename T>
auto digit_width(T x) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, int>::type
{
  assert(x >= 0 && "argument must be nonnegative");
  return x == 0 ? 1 : ilog10(x) + 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPERATION_LOG10_HPP
