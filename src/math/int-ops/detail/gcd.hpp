#ifndef AAL_SRC_MATH_INT_OPS_DETAIL_GCD_HPP
#define AAL_SRC_MATH_INT_OPS_DETAIL_GCD_HPP

#include "../../../macros/constexpr.hpp"
#include "../abs.hpp"

namespace aal { namespace detail {

template <typename TOp, typename... Ts>
AAL_CONSTEXPR14 auto gcd_lcm_selector(Ts&&... nums) noexcept -> typename std::enable_if<sizeof...(Ts) >= 2, typename TOp::operand_type>::type
{
  using result_type = typename TOp::operand_type;
  make_unsigned_t<result_type> mags[sizeof...(Ts)] {iabs(nums)...};

#ifndef NDEBUG
  for (auto i : mags)
    assert(static_cast<result_type>(i) >= 0 && "some magnitudes cannot be represented in the common type");
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

}} // namespace aal::detail

#endif // AAL_SRC_MATH_INT_OPS_DETAIL_GCD_HPP
