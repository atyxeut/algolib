#ifndef AAL_SRC_MATH_INT_OPS_HPP
#define AAL_SRC_MATH_INT_OPS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops.hpp */

#include "../type_traits.hpp"
#include <cassert>

namespace aal {

template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 bool iadd_overflows(T1 lhs, T2 rhs) noexcept
{
  static_assert(conjunction<is_integral<T1>, is_integral<T2>>::value, "given operands must be integers");
  assert(lhs >= 0 && rhs >= 0 && "given operands must be nonnegative");
  return rhs > lim<TResult>::max() || lhs > lim<TResult>::max() - rhs;
}

template <typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 bool imul_overflows(T1 lhs, T2 rhs) noexcept
{
  static_assert(conjunction<is_integral<T1>, is_integral<T2>>::value, "given operands must be integers");
  assert(lhs >= 0 && rhs >= 0 && "given operands must be nonnegative");
  return rhs == 0 ? false : lhs > lim<TResult>::max() / rhs;
}

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
