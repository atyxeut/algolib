#ifndef AAL_SRC_MATH_OPERATOR_GCD_HPP
#define AAL_SRC_MATH_OPERATOR_GCD_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/operator/gcd.hpp */

#include <tuple>

#include "../../type-trait/operator.hpp"
#include "../integral/basic-operation/overflow_detection.hpp"

namespace aal { namespace op {

// class template representing operator gcd
// auto gcd = aal::op::gcd<int> {};
// int ans = gcd(3, 6);
template <nonbool_integral T>
struct gcd
{
  using operator_category = binary_operator_tag;
  using operand_type = std::tuple<T, T>;

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

// class template representing operator lcm
// auto lcm = aal::op::lcm<int> {};
// int ans = lcm(3, 18);
template <nonbool_integral T>
struct lcm
{
  using operator_category = binary_operator_tag;
  using operand_type = std::tuple<T, T>;

  static constexpr T identity_elem = 1; // lcm(1, a) = a
  static constexpr T absorbing_elem = 0; // lcm(0, a) = 0

  [[nodiscard]] constexpr T operator ()(T a, T b) const noexcept
  {
    assert(!overflows::imul<T>(a / gcd<T> {}(a, b), b) && "the lcm cannot be represented");
    return a / gcd<T> {}(a, b) * b;
  }
};

}} // namespace aal::op

#endif // AAL_SRC_MATH_OPERATOR_GCD_HPP
