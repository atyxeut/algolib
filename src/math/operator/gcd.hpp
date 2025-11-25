#ifndef AAL_SRC_MATH_OPERATOR_GCD_HPP
#define AAL_SRC_MATH_OPERATOR_GCD_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/operator/gcd.hpp */

#include <cassert>
#include <limits>
#include <tuple>

#include "../../concept/integral.hpp"
#include "../../macro/warning.hpp"
#include "../../type-trait/operator.hpp"
#include "../integral/basic-operation/overflow_detection.hpp"

namespace aal::op {

// class template representing operator gcd
// auto gcd = aal::op::gcd<int> {};
// int ans = gcd(3, 6);
template <nonbool_integral T>
struct gcd
{
  using operator_category = binary_operator_tag;
  using operand_type = std::tuple<T, T>;

  static constexpr T neutral_element {0}; // gcd(0, a) = a
  static constexpr T absorbing_element {1}; // gcd(1, a) = 1

  [[nodiscard]] static constexpr T operator ()(T a, T b) noexcept
  {
    T t;
    while (b != 0) {
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

  static constexpr T neutral_element = {1}; // lcm(1, a) = a
  static constexpr T absorbing_element = {0}; // lcm(0, a) = 0

  AAL_INT_WCONVERSION_WCOMPARE_PUSH

  [[nodiscard]] static constexpr T operator ()(T a, T b) noexcept
  {
    assert(!ioverflows::mul(a / gcd<T>::operator ()(a, b), b, std::numeric_limits<T>::max()) && "the lcm cannot be represented");
    return a / gcd<T>::operator ()(a, b) * b;
  }

  AAL_INT_WCONVERSION_WCOMPARE_POP
};

} // namespace aal::op

#endif // AAL_SRC_MATH_OPERATOR_GCD_HPP
