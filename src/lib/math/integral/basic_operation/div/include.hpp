#ifndef AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_DIV_INCLUDE_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_DIV_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/basic_operation/div/include.hpp */

#include <utility>

#include "../../../../../fundamental/macro/warning.hpp"
#include "../../../../../fundamental/type_trait/integral.hpp"

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
  using type = std::conditional_t<is_unsigned_v<type2>, type1, make_larger_width_t<make_signed_t<type1>>>;
};

AAL_INT_WCONVERSION_WCOMPARE_PUSH()

template <mode Mode, typename T1, typename T2>
constexpr auto selector(T1 lhs, T2 rhs) noexcept
{
  using result_type = final_result<T1, T2>::type;

  // -0 = 0, so no need to consider lhs = 0, rhs < 0 and lhs < 0, rhs = 0 cases
  bool is_ans_negative = (lhs < 0) != (rhs < 0);

  auto lhs_abs = iabs(lhs);
  auto rhs_abs = iabs(rhs);

  auto q = lhs_abs / rhs_abs;
  bool modify_ans = lhs_abs % rhs_abs != 0;

#ifndef NDEBUG
  constexpr auto res_max = std::numeric_limits<result_type>::max();
  if (q > 0) { // no way to overflow if q = 0
    if (!modify_ans) { // r = 0, |ans| = q
      if (is_ans_negative) // ans = -q, so q must be <= result_max + 1
        assert(!ioverflows::add(q - 1, 0, res_max) && "the result cannot be represented");
      else // ans = q, so q must be <= result_max
        assert(!ioverflows::add(q, 0, res_max) && "the result cannot be represented");
    }
    else { // r != 0, so |rhs| >= 2, so q is at most floor(unsigned_result_max / 2) = result_max
      // neg + floor: ans = -q - 1, so q + 1 must be <= result_max + 1 (always satisfied)
      // neg + ceil: ans = -q + 1, so q - 1 must be <= result_max + 1 (always satisfied)
      // pos + floor: ans = q, so q must be <= result_max (always satisfied)
      if (!is_ans_negative && Mode == mode::ceil) // ans = q + 1, so q + 1 must be <= result_max
        assert(!ioverflows::add(q, 1, res_max) && "the ceil div result cannot be represented");
    }
  }
#endif // NDEBUG

  if constexpr (Mode == mode::floor)
    return is_ans_negative ? -static_cast<result_type>(q + modify_ans) : static_cast<result_type>(q);
  else
    return is_ans_negative ? -static_cast<result_type>(q) : static_cast<result_type>(q + modify_ans);
}

AAL_INT_WCONVERSION_WCOMPARE_POP()

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

#endif // AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_DIV_INCLUDE_HPP
