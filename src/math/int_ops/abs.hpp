#ifndef AAL_SRC_MATH_INT_OPS_ABS_HPP
#define AAL_SRC_MATH_INT_OPS_ABS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops/abs.hpp */

#include "../../type_traits/integral.hpp"

namespace aal {

template <typename T>
constexpr auto iabs(T n) noexcept -> typename ::std::enable_if<is_unsigned<T>::value, T>::type
{
  return n;
}

template <typename T>
constexpr auto iabs(T n) noexcept -> typename ::std::enable_if<is_signed<T>::value, make_unsigned<T>>::type::type
{
  // for negative n, ~n + 1 is |n| if the bit representation is two's complement
  return n >= 0 ? n : ~static_cast<make_unsigned_t<T>>(n) + 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_ABS_HPP
