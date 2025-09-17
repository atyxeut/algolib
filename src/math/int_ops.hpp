#ifndef AAL_SRC_MATH_INT_OPS_HPP
#define AAL_SRC_MATH_INT_OPS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops.hpp */

#include "overflow_detection.hpp"

namespace aal {

template <typename T>
constexpr auto iabs(T n) noexcept -> t_enable_if_t<is_unsigned<T>, T>
{
  return n;
}

template <typename T>
constexpr auto iabs(T n) noexcept -> typename t_enable_if_t<is_signed<T>, make_unsigned<T>>::type
{
  return n >= 0 ? n : ~static_cast<make_unsigned_t<T>>(n) + 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_HPP
