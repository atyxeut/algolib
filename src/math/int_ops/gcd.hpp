#ifndef AAL_SRC_MATH_INT_OPS_GCD_HPP
#define AAL_SRC_MATH_INT_OPS_GCD_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops/gcd.hpp */

#include "../../type_traits/common_type.hpp"
#include "../operator/categories.hpp"
#include "iabs.hpp"
#include "overflow_detection.hpp"
#include <utility>

namespace aal {

namespace op {

template <typename T>
struct gcd
{
// clang-format off
  using category     = binary_operator_tag;
  using operand_type = typename std::enable_if<is_nonbool_integral<T>::value, T>::type;
  
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

template <typename T>
struct lcm
{
// clang-format off
  using category     = binary_operator_tag;
  using operand_type = typename std::enable_if<is_nonbool_integral<T>::value, T>::type;
  
  static constexpr T identity_elem  = 1; // lcm(1, a) = a
  static constexpr T absorbing_elem = 0; // lcm(0, a) = 0
// clang-format on

  AAL_CONSTEXPR14 T operator ()(T a, T b) const noexcept
  {
    assert(!imul_overflows<T>(a / gcd<T> {}(a, b), b) && "the lcm cannot be represented");
    return a / gcd<T> {}(a, b) * b;
  }
};

} // namespace op

namespace details {

template <typename TOp, typename... Ts, typename TResult = typename std::enable_if<sizeof...(Ts) >= 2, typename TOp::operand_type>::type>
AAL_CONSTEXPR14 TResult gcd_lcm_selector(Ts&&... nums) noexcept
{
  make_unsigned_t<TResult> mags[sizeof...(Ts)] {iabs(nums)...};

#ifndef NDEBUG
  for (auto i : mags)
    assert(static_cast<TResult>(i) >= 0 && "not all magnitudes can be represented in the common type");
#endif // NDEBUG

  TOp op;
  TResult ans = *mags;
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

template <typename... Ts, typename TResult = typename std::enable_if<conjunction<is_nonbool_integral<Ts>...>::value, common_type_t<remove_cv_t<Ts>...>>::type>
AAL_CONSTEXPR14 TResult gcd(Ts&&... nums) noexcept
{
  return details::gcd_lcm_selector<op::gcd<TResult>>(std::forward<Ts>(nums)...);
}

template <typename... Ts, typename TResult = typename std::enable_if<conjunction<is_nonbool_integral<Ts>...>::value, common_type_t<remove_cv_t<Ts>...>>::type>
AAL_CONSTEXPR14 TResult lcm(Ts&&... nums) noexcept
{
  return details::gcd_lcm_selector<op::lcm<TResult>>(std::forward<Ts>(nums)...);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_GCD_HPP
