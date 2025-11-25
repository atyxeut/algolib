#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_INCLUDE_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/integral/basic-operation/gcd/include.hpp */

#include "../../../operator/gcd.hpp"
#include "../abs.hpp"

namespace aal {

namespace detail {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

template <typename TOp, typename... Ts>
auto gcd_lcm_impl(Ts... nums) noexcept -> typename std::tuple_element<0, typename TOp::operand_type>::type
{
  using result_type = typename std::tuple_element<0, typename TOp::operand_type>::type;
  make_unsigned_t<result_type> mags[sizeof...(Ts)] {iabs(nums)...};

#ifndef NDEBUG
  for (auto i : mags)
    assert(static_cast<result_type>(i) >= 0 && "some magnitudes cannot be represented in the common type");
#endif // NDEBUG

  TOp op;
  result_type ans = *mags;

  for (auto it = mags + 1, it_end = mags + sizeof...(Ts); it != it_end; ++it) {
    if (*it == op.absorbing_elem)
      return op.absorbing_elem;
    if (*it == op.neutral_elem)
      continue;
    ans = op(ans, *it);
  }
  return ans;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace detail

// compute gcd(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// long long ans = aal::gcd(28, 21LL, -7, 0);
// ans is 7
template <typename... Ts>
auto gcd(Ts... nums) noexcept ->
  typename std::enable_if<(sizeof...(Ts) >= 2) && conjunction<is_nonbool_integral<Ts>...>::value, typename std::common_type<Ts...>::type>::type
{
  using result_type = typename std::common_type<Ts...>::type;
  return detail::gcd_lcm_impl<op::gcd<result_type>>(nums...);
}

// compute lcm(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// u128 ans = aal::lcm(28, -21, 7, 49, u128(1));
// ans is 588
template <typename... Ts>
auto lcm(Ts... nums) noexcept ->
  typename std::enable_if<(sizeof...(Ts) >= 2) && conjunction<is_nonbool_integral<Ts>...>::value, typename std::common_type<Ts...>::type>::type
{
  using result_type = typename std::common_type<Ts...>::type;
  return detail::gcd_lcm_impl<op::lcm<result_type>>(nums...);
}

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_INCLUDE_HPP
