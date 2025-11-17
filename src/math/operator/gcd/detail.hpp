#ifndef AAL_SRC_MATH_OPERATOR_GCD_DETAIL_HPP
#define AAL_SRC_MATH_OPERATOR_GCD_DETAIL_HPP

#include "../../../type-trait/operator.hpp"
#include "../../int-operation/overflow-detection/include.hpp"

namespace aal { namespace op { namespace detail {

template <typename T>
struct gcd_impl
{
  using operator_category = binary_operator_tag;
  using operand_type = T;

  static constexpr T identity_elem = 0; // gcd(0, a) = a
  static constexpr T absorbing_elem = 1; // gcd(1, a) = 1

  [[nodiscard]] constexpr T operator ()(T a, T b) const noexcept
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
struct lcm_impl
{
  using operator_category = binary_operator_tag;
  using operand_type = T;

  static constexpr T identity_elem = 1; // lcm(1, a) = a
  static constexpr T absorbing_elem = 0; // lcm(0, a) = 0

  [[nodiscard]] constexpr T operator ()(T a, T b) const noexcept
  {
    assert(!ioverflows::mul<T>(a / gcd_impl<T> {}(a, b), b) && "the lcm cannot be represented");
    return a / gcd_impl<T> {}(a, b) * b;
  }
};

}}} // namespace aal::op::detail

#endif // AAL_SRC_MATH_OPERATOR_GCD_DETAIL_HPP
