#ifndef AAL_SRC_MATH_INT_OPS_IDIV_HPP
#define AAL_SRC_MATH_INT_OPS_IDIV_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/idiv.hpp */

#include "iabs.hpp"
#include "overflow_detection.hpp"
#include <utility>

namespace aal {

namespace details {

enum class idiv_mode
{
  floor,
  ceil
};

template <typename TDividend, typename TDivisor>
struct idiv_result
{
  static_assert(conjunction<is_nonbool_integral<TDividend>, is_nonbool_integral<TDivisor>>::value, "given two types must be nonbool integral");
  // cv-qualifiers are removed after integral promotion
  using type1 = decltype(+std::declval<TDividend>());
  using type2 = decltype(+std::declval<TDivisor>());

  // branch 1: type2 is unsigned, then the divisor is always positive, so the result never overflows type1

  // branch 2: type2 is signed, the result type has to be a signed type larger than type1
  //   e.g. -2147483648 (int) / -1 = 2147483648 (requires long long)
  //   e.g. 4294967295 (unsigned int) / -1 = -4294967295 (requires long long)

  // obtains a type that guarantees to be able to represent the result, unless there is no such type
  using type = typename std::conditional<is_unsigned<type2>::value, type1, make_larger_width_t<make_signed_t<type1>>>::type;
};

template <idiv_mode Mode, typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_impl(T1 lhs, T2 rhs) noexcept -> typename idiv_result<T1, T2>::type
{
  assert(rhs != 0 && "divisor cannot be 0");
  using result_type = typename idiv_result<T1, T2>::type;

  // -0 = 0, so no need to consider lhs = 0, rhs < 0 and lhs < 0, rhs = 0 cases
  bool is_ans_negative = lhs < 0 != rhs < 0;
  auto lhs_abs = iabs(lhs);
  auto rhs_abs = iabs(rhs);
  auto q = lhs_abs / rhs_abs;
  bool modify_ans = lhs_abs % rhs_abs != 0;

#ifndef NDEBUG
  if (q > 0) { // no way to overflow if q = 0
    if (!modify_ans) { // r = 0, |ans| = q
      if (is_ans_negative) // ans = -q, so q must be <= result_max + 1
        assert(!iadd_overflows<result_type>(q - 1, 0) && "the result cannot be represented");
      else // ans = q, so q must be <= result_max
        assert(!iadd_overflows<result_type>(q, 0) && "the result cannot be represented");
    }
    else { // r != 0, so |rhs| >= 2, so q is at most floor(unsigned_result_max / 2) = result_max
      if (is_ans_negative) {
        if (Mode == idiv_mode::floor) // ans = -q - 1, so q + 1 must be <= result_max + 1, which is always satisfied
          ;
        if (Mode == idiv_mode::ceil) // ans = -q + 1, so q - 1 must be <= result_max + 1, which is always satisfied
          ;
      }
      else {
        if (Mode == idiv_mode::floor) // ans = q, so q must be <= result_max, which is always satisfied
          ;
        if (Mode == idiv_mode::ceil) // ans = q + 1, so q + 1 must be <= result_max
          assert(!iadd_overflows<result_type>(q, 1) && "the ceil div result cannot be represented");
      }
    }
  }
#endif // NDEBUG

  if (Mode == idiv_mode::floor)
    return is_ans_negative ? -static_cast<result_type>(q + modify_ans) : q;

  return is_ans_negative ? -static_cast<result_type>(q) : q + modify_ans;
}

} // namespace details

template <typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_floor(T1 lhs, T2 rhs) noexcept -> typename details::idiv_result<T1, T2>::type
{
  return details::idiv_impl<details::idiv_mode::floor>(lhs, rhs);
}

template <typename T1, typename T2>
AAL_CONSTEXPR14 auto idiv_ceil(T1 lhs, T2 rhs) noexcept -> typename details::idiv_result<T1, T2>::type
{
  return details::idiv_impl<details::idiv_mode::ceil>(lhs, rhs);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_IDIV_HPP
