#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_DETAIL_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_DETAIL_HPP

#include "../abs.hpp"

namespace aal { namespace detail {

template <typename TOp, typename... Ts>
auto gcd_lcm_impl(Ts... nums) noexcept -> typename TOp::operand_type
{
  using result_type = typename TOp::operand_type;

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
    if (*it == op.identity_elem)
      continue;
    ans = op(ans, *it);
  }

  return ans;
}

}} // namespace aal::detail

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_GCD_DETAIL_HPP
