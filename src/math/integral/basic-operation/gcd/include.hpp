#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_INCLUDE_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic-operation/gcd/include.hpp */

#include "../../../../macro/warning.hpp"
#include "../../../operator/gcd.hpp"
#include "../abs.hpp"

namespace aal {

namespace detail {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

template <typename TOp, typename... Ts>
constexpr auto gcd_lcm_impl(Ts... nums) noexcept
{
  using result_type = std::tuple_element_t<0, typename TOp::operand_type>;
  make_unsigned_t<result_type> mags[sizeof...(Ts)] {iabs(nums)...};

#ifndef NDEBUG
  for (auto i : mags)
    assert(static_cast<result_type>(i) >= 0 && "some magnitudes cannot be represented in the common type");
#endif // NDEBUG

  result_type ans = *mags;
  for (auto it = mags + 1, it_end = mags + sizeof...(Ts); it != it_end; ++it) {
    if (*it == TOp::absorbing_element)
      return TOp::absorbing_element;
    if (*it == TOp::neutral_element)
      continue;
    ans = TOp::operator ()(ans, *it);
  }
  return ans;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace detail

// compute gcd(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// long long ans = aal::gcd(28, 21LL, -7, 0);
// ans is 7
template <nonbool_integral... Ts> requires (sizeof...(Ts) >= 2)
[[nodiscard]] constexpr auto gcd(Ts... nums) noexcept
{
  return detail::gcd_lcm_impl<op::gcd<std::common_type_t<Ts...>>>(nums...);
}

// compute lcm(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// u128 ans = aal::lcm(28, -21, 7, 49, u128(1));
// ans is 588
template <nonbool_integral... Ts> requires (sizeof...(Ts) >= 2)
[[nodiscard]] constexpr auto lcm(Ts... nums) noexcept
{
  return detail::gcd_lcm_impl<op::lcm<std::common_type_t<Ts...>>>(nums...);
}

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_INCLUDE_HPP
