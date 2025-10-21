#ifndef AAL_SRC_MATH_INT_OPS_GCD_HPP
#define AAL_SRC_MATH_INT_OPS_GCD_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/gcd.hpp */

#include "../operator/categories.hpp"
#include "iabs.hpp"
#include "overflow_detection.hpp"
#include <utility>

namespace aal {

namespace op {

namespace details {

template <typename T, typename = std::enable_if<is_nonbool_integral<T>::value>>
struct gcd_impl
{
// clang-format off
  using category     = binary_operator_tag;
  using operand_type = T;
  static constexpr T identity_elem  = 0; // gcd(0, a) = a
  static constexpr T absorbing_elem = 1; // gcd(1, a) = 1
// clang-format on

  AAL_CONSTEXPR14 T operator ()(T a, T b) const noexcept
  {
    for (T t; b != 0;) {
      t = a % b;
      a = b;
      b = t;
    }
    return a;
  }
};

template <typename T, typename = std::enable_if<is_nonbool_integral<T>::value>>
struct lcm_impl
{
// clang-format off
  using category     = binary_operator_tag;
  using operand_type = T;
  static constexpr T identity_elem  = 1; // lcm(1, a) = a
  static constexpr T absorbing_elem = 0; // lcm(0, a) = 0
// clang-format on

  AAL_CONSTEXPR14 T operator ()(T a, T b) const noexcept
  {
    assert(!imul_overflows<T>(a / gcd_impl<T> {}(a, b), b) && "the lcm cannot be represented");
    return a / gcd_impl<T> {}(a, b) * b;
  }
};

} // namespace details

template <typename T>
using gcd = details::gcd_impl<T>;

template <typename T>
using lcm = details::lcm_impl<T>;

} // namespace op

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

template <typename... Ts>
AAL_CONSTEXPR14 auto gcd(Ts&&... nums) noexcept -> typename std::common_type<remove_cv_t<Ts>...>::type
{
  static_assert(conjunction<is_nonbool_integral<Ts>...>::value, "arguments must be nonbool integers");
  using result_type = typename std::common_type<remove_cv_t<Ts>...>::type;
  return details::gcd_lcm_selector<op::gcd<result_type>>(std::forward<Ts>(nums)...);
}

template <typename... Ts>
AAL_CONSTEXPR14 auto lcm(Ts&&... nums) noexcept -> typename std::common_type<remove_cv_t<Ts>...>::type
{
  static_assert(conjunction<is_nonbool_integral<Ts>...>::value, "arguments must be nonbool integers");
  using result_type = typename std::common_type<remove_cv_t<Ts>...>::type;
  return details::gcd_lcm_selector<op::lcm<result_type>>(std::forward<Ts>(nums)...);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_GCD_HPP
