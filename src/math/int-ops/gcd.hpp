#ifndef AAL_SRC_MATH_INT_OPS_GCD_HPP
#define AAL_SRC_MATH_INT_OPS_GCD_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/gcd.hpp */

// provide function templates to calculate gcd and lcm of a list of integers, see gcd.md for extra information

#include "../operator/gcd.hpp"
#include "iabs.hpp"
#include "overflow_detection.hpp"
#include <utility>

namespace aal {

namespace details {

template <typename TOp, typename... Ts>
AAL_CONSTEXPR14 auto gcd_lcm_selector(Ts&&... nums) noexcept -> typename TOp::operand_type
{
  static_assert(sizeof...(Ts) >= 2, "must give at least 2 arguments");
  using result_type = typename TOp::operand_type;
  make_unsigned_t<result_type> mags[sizeof...(Ts)] {iabs(nums)...};

#ifndef NDEBUG
  for (auto i : mags)
    assert(static_cast<result_type>(i) >= 0 && "not all magnitudes can be represented in the common type");
#endif // NDEBUG

  TOp op;
  result_type ans = *mags;
  for (auto iter = mags + 1, end = mags + sizeof...(Ts); iter != end; ++iter) {
    if (*iter == op.absorbing_elem)
      return op.absorbing_elem;
    if (*iter == op.identity_elem)
      continue;
    ans = op(ans, *iter);
  }
  return ans;
}

} // namespace details

// compute gcd(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// long long ans = aal::gcd(28, 21LL, -7, 0);
// ans is 7
template <typename... Ts>
AAL_CONSTEXPR14 auto gcd(Ts&&... nums) noexcept -> typename std::common_type<remove_cv_t<Ts>...>::type
{
  static_assert(conjunction<is_nonbool_integral<Ts>...>::value, "arguments must be nonbool integers");
  using result_type = typename std::common_type<remove_cv_t<Ts>...>::type;
  return details::gcd_lcm_selector<op::gcd<result_type>>(std::forward<Ts>(nums)...);
}

// compute lcm(x_1, x_2, ..., x_n), can correctly handle operands that have different width and signedness
// u128 ans = aal::lcm(28, -21, 7, 49, u128(1));
// ans is 588
template <typename... Ts>
AAL_CONSTEXPR14 auto lcm(Ts&&... nums) noexcept -> typename std::common_type<remove_cv_t<Ts>...>::type
{
  static_assert(conjunction<is_nonbool_integral<Ts>...>::value, "arguments must be nonbool integers");
  using result_type = typename std::common_type<remove_cv_t<Ts>...>::type;
  return details::gcd_lcm_selector<op::lcm<result_type>>(std::forward<Ts>(nums)...);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_GCD_HPP
