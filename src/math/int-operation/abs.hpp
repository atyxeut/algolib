#ifndef AAL_SRC_MATH_INT_OPERATION_ABS_HPP
#define AAL_SRC_MATH_INT_OPERATION_ABS_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-operation/abs.hpp */

#include "../../concept/integral.hpp"

namespace aal {

// an improved version of std::abs, can handle unsigned integer types and i/u128, and never overflows
//   no compilation error: unsigned int _ = aal::iabs(1u);
//   no overflow: unsigned int _ = aal::iabs(-2147483647 - 1);
template <nonbool_integral T>
[[nodiscard]] constexpr auto iabs(T n) noexcept
{
  using result_type = make_unsigned_t<T>;
  // for negative n, ~n + 1 is |n| if the bit representation is two's complement
  return n >= 0 ? static_cast<result_type>(n) : ~static_cast<result_type>(n) + 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPERATION_ABS_HPP
