#ifndef AAL_SRC_MATH_INT_OPS_DIV_HPP
#define AAL_SRC_MATH_INT_OPS_DIV_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops/div.hpp */

#include "../operators/basics.hpp"
#include "abs.hpp"
#include "overflow_detection.hpp"
#include <utility>

namespace aal {

namespace details {

template <typename T1, typename T2>
struct idiv_result
{
  static_assert(conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, "given two types must be nonbool integral");

  // cv-qualifiers are removed after integral promotion
  using dividend_type = decltype(+::std::declval<T1>()); // the "type1" in the comments
  using divisor_type  = decltype(+::std::declval<T2>()); // the "type2" in the comments

  // branch 1: type2 is unsigned, i.e. the divisor is positive, the result never overflows type1

  // branch 2: type2 is signed, the result type has to be a signed type larger than type1
  //   e.g. -2147483648 (int) / -1 = 2147483648
  //   e.g. 4294967295 (unsigned int) / -1 = -4294967295
  //   both of the above require long long as the result type

  using type = typename ::std::conditional<is_unsigned<divisor_type>::value, dividend_type, make_larger_width_t<make_signed_t<dividend_type>>>::type;

  // if dividend_type is i/u128, then the potential overflow is inevitable when type2 is signed, since there's no larger type
};

template <ops::mode Mode, typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_impl(T1 lhs, T2 rhs) noexcept -> typename idiv_result<T1, T2>::type
{
  assert(rhs != 0 && "divisor cannot be 0");
  using result_type = typename idiv_result<T1, T2>::type;

  // -0 = 0, so no need to consider 0, < 0 and < 0, 0
  bool is_quotient_negative = lhs < 0 ^ rhs < 0;

  auto lhs_abs = iabs(lhs);
  auto rhs_abs = iabs(rhs);

  auto q               = lhs_abs / rhs_abs;
  bool modify_quotient = lhs_abs % rhs_abs != 0;

#ifndef NDEBUG
  // idiv_result<T1, T2>::type guarantees a type that can represent the result,
  // overflow occurs only when there's no such a type, i.e. the result requires a type larger than i/u128

  if (q > 0) { // no way to overflow if q = 0
    if (!modify_quotient) { // in this case, |ans| = q
      if (is_quotient_negative) // the answer is -q, so q must be <= result_max + 1
        assert(!iadd_overflows<result_type>(q - 1, 0) && "the result cannot be represented");
      else // the answer is q, so q must be <= result_max
        assert(!iadd_overflows<result_type>(q, 0) && "the result cannot be represented");
    }
    else { // in this case, r != 0, then |rhs| >= 2 is guaranteed, so q is at most floor(uresult_max / 2) = result_max
      if (is_quotient_negative) {
        if (Mode == ops::mode::floor) // the answer is -q - 1, so q + 1 must be <= result_max + 1, which is always satisfied
          ;
        if (Mode == ops::mode::ceil) // the answer is -q + 1, so q - 1 must be <= result_max + 1, which is always satisfied
          ;
      }
      else {
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
AAL_CONSTEXPR14 auto idiv_floor(T1 lhs, T2 rhs) noexcept -> typename details::idiv_result<T1, T2>::type
{
  return details::idiv_impl<ops::mode::floor>(lhs, rhs);
}

template <typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_ceil(T1 lhs, T2 rhs) noexcept -> typename details::idiv_result<T1, T2>::type
{
  return details::idiv_impl<ops::mode::ceil>(lhs, rhs);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_DIV_HPP
