#ifndef AAL_SRC_MATH_INT_OPS_IABS_HPP
#define AAL_SRC_MATH_INT_OPS_IABS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops/iabs.hpp */

#include "../../type_traits/integral.hpp"

namespace aal {

template <typename T>
constexpr auto iabs(T n) noexcept -> make_unsigned_t<T> // implies is_integral<T>::value == true
{
  // for negative n, ~n + 1 is |n| if the bit representation is two's complement
  return n >= 0 ? n : ~static_cast<make_unsigned_t<T>>(n) + 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_IABS_HPP
