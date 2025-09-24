#ifndef AAL_SRC_MATH_INT_OPS_HPP
#define AAL_SRC_MATH_INT_OPS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops.hpp */

#include "operators.hpp"

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

namespace details {

template <ops::mode Mode, typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_impl(T1 lhs, T2 rhs) noexcept -> idiv_result_t<T1, T2>
{
  assert(rhs != 0 && "divisor cannot be 0");
  using result_type = idiv_result_t<T1, T2>;

  // -0 = 0, so no need to consider 0, < 0 and < 0, 0
  bool is_quotient_negative = lhs < 0 ^ rhs < 0;

  auto lhs_abs = iabs(lhs);
  auto rhs_abs = iabs(rhs);

  auto q               = lhs_abs / rhs_abs;
  bool modify_quotient = lhs_abs % rhs_abs != 0;

#ifndef NDEBUG
  // idiv_result_t<T1, T2> guarantees a type that can represent the result,
  // overflow occurs only when there's no such a type, i.e. the result requires a type larger than i/u128

  if (q > 0) // no way to overflow if q = 0
  {
    if (!modify_quotient) // in this case, |ans| = q
    {
      if (is_quotient_negative) // the answer is -q, so q must be <= result_max + 1
        assert(!iadd_overflows<result_type>(q - 1, 0) && "the result cannot be represented");
      else // the answer is q, so q must be <= result_max
        assert(!iadd_overflows<result_type>(q, 0) && "the result cannot be represented");
    }
    else // in this case, r != 0, then |rhs| >= 2 is guaranteed, so q is at most floor(uresult_max / 2) = result_max
    {
      if (is_quotient_negative)
      {
        if (Mode == ops::mode::floor) // the answer is -q - 1, so q + 1 must be <= result_max + 1, which is always satisfied
          ;
        if (Mode == ops::mode::ceil) // the answer is -q + 1, so q - 1 must be <= result_max + 1, which is always satisfied
          ;
      }
      else
      {
        if (Mode == ops::mode::floor) // the answer is q, so q must be <= result_max, which is always satisfied
          ;
        if (Mode == ops::mode::ceil) // the answer is q + 1, so q + 1 must be <= result_max
          assert(!iadd_overflows<result_type>(q, 1) && "the ceil div result cannot be represented");
      }
    }
  }
#endif // NDEBUG

  if (Mode == ops::mode::floor)
    return !is_quotient_negative ? q : -static_cast<result_type>(q + modify_quotient);

  return is_quotient_negative ? -static_cast<result_type>(q) : q + modify_quotient;
}

} // namespace details

template <typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_floor(T1 lhs, T2 rhs) noexcept -> idiv_result_t<T1, T2>
{
  return details::idiv_impl<ops::mode::floor>(lhs, rhs);
}

template <typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_ceil(T1 lhs, T2 rhs) noexcept -> idiv_result_t<T1, T2>
{
  return details::idiv_impl<ops::mode::ceil>(lhs, rhs);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_HPP
