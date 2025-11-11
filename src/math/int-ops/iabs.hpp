#ifndef AAL_SRC_MATH_INT_OPS_IABS_HPP
#define AAL_SRC_MATH_INT_OPS_IABS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/iabs.hpp */

#include "../../type-traits/integral.hpp"

namespace aal {

// an improved version of std::abs, can handle unsigned integer types and i/u128, and never overflows
// no compilation error: unsigned int _ = aal::iabs(1u);
// no overflow: unsigned int _ = aal::iabs(-2147483647 - 1);
template <typename T>
constexpr auto iabs(T n) noexcept -> make_unsigned_t<T>
{
  using result_type = make_unsigned_t<T>;
  // for negative n, ~n + 1 is |n| if the bit representation is two's complement
  return n >= 0 ? static_cast<result_type>(n) : ~static_cast<result_type>(n) + 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_IABS_HPP
