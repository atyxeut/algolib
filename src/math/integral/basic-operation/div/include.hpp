#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_DIV_INCLUDE_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_DIV_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/integral/basic-operation/div/include.hpp */

#include <utility>

#include "../abs.hpp"
#include "../overflow_detection.hpp"

namespace aal::idiv {

namespace detail {

enum class mode
{
  floor,
  ceil
};

template <typename TDividend, typename TDivisor>
struct final_result
{
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

template <typename TDividend, typename TDivisor>
using final_result_t = typename final_result<TDividend, TDividend>::type;

template <mode Mode, typename T1, typename T2>
constexpr auto selector(T1 lhs, T2 rhs) noexcept
{
  using result_type = final_result_t<T1, T2>;

  // -0 = 0, so no need to consider lhs = 0, rhs < 0 and lhs < 0, rhs = 0 cases
  bool is_ans_negative = (lhs < 0) != (rhs < 0);

  using op_common_type = std::common_type_t<decltype(iabs(lhs)), decltype(iabs(rhs))>;
  auto lhs_abs = static_cast<op_common_type>(iabs(lhs));
  auto rhs_abs = static_cast<op_common_type>(iabs(rhs));

  auto q = lhs_abs / rhs_abs;
  bool modify_ans = lhs_abs % rhs_abs != 0;

#ifndef NDEBUG
  if (q > 0) { // no way to overflow if q = 0
    if (!modify_ans) { // r = 0, |ans| = q
      if (is_ans_negative) // ans = -q, so q must be <= result_max + 1
        assert(!overflows::iadd<result_type>(q - 1, 0) && "the result cannot be represented");
      else // ans = q, so q must be <= result_max
        assert(!overflows::iadd<result_type>(q, 0) && "the result cannot be represented");
    }
    else { // r != 0, so |rhs| >= 2, so q is at most floor(unsigned_result_max / 2) = result_max
      if (is_ans_negative) {
        if (Mode == mode::floor) {
          // ans = -q - 1, so q + 1 must be <= result_max + 1, which is always satisfied
        }
        if (Mode == mode::ceil) {
          // ans = -q + 1, so q - 1 must be <= result_max + 1, which is always satisfied
        }
      }
      else {
        if (Mode == mode::floor) {
          // ans = q, so q must be <= result_max, which is always satisfied
        }
        if (Mode == mode::ceil) {
          // ans = q + 1, so q + 1 must be <= result_max
          assert(!overflows::iadd<result_type>(q, 1) && "the ceil div result cannot be represented");
        }
      }
    }
  }
#endif // NDEBUG

  if constexpr (Mode == mode::floor)
    return is_ans_negative ? -static_cast<result_type>(q + modify_ans) : static_cast<result_type>(q);
  else
    return is_ans_negative ? -static_cast<result_type>(q) : static_cast<result_type>(q + modify_ans);
}

} // namespace detail

// compute floor(a / b) for integers a, b without introducing floating-point numbers
// can correctly handle operands that have different width and signedness
// int ans = aal::idiv::floor(5, 2);
// int ans = aal::idiv::floor(-5, 2);
// int ans = aal::idiv::floor(-2147483647 - 1, 1ull);
// ans is 2, -3, -2147483648 respectively
template <nonbool_integral T1, nonbool_integral T2>
[[nodiscard]] constexpr auto floor(T1 lhs, T2 rhs) noexcept
{
  assert(rhs != 0 && "divisor cannot be 0");
  return detail::selector<detail::mode::floor>(lhs, rhs);
}

// compute ceil(a / b) for integers a, b without introducing floating-point numbers
// can correctly handle operands that have different width and signedness
// int ans = aal::idiv::ceil(5, 2); // 3
// int ans = aal::idiv::ceil(-5, 2); // -2
// long long ans = aal::idiv::ceil(-2147483647 - 1, -1); // 2147483648, no overflow
// ans is 3, -2, 2147483648 (no overflow) respectively
template <nonbool_integral T1, nonbool_integral T2>
[[nodiscard]] constexpr auto ceil(T1 lhs, T2 rhs) noexcept
{
  assert(rhs != 0 && "divisor cannot be 0");
  return detail::selector<detail::mode::ceil>(lhs, rhs);
}

} // namespace aal::idiv

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_DIV_INCLUDE_HPP
