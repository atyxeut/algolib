#ifndef AAL_SRC_MATH_OPERATOR_GCD_HPP
#define AAL_SRC_MATH_OPERATOR_GCD_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/operator/gcd.hpp */

#include <cassert>
#include <limits>
#include <tuple>

#include "../../macro/warning.hpp"
#include "../../type-trait/integral.hpp"
#include "../../type-trait/operator.hpp"
#include "../integral/basic-operation/overflow_detection.hpp"

namespace aal { namespace op {

namespace detail {

template <typename T, typename = typename std::enable_if<is_nonbool_integral<T>::value>::type>
struct gcd_impl
{
  using operator_category = binary_operator_tag;
  using operand_type = std::tuple<T, T>;

  static constexpr T neutral_elem {0}; // gcd(0, a) = a
  static constexpr T absorbing_elem {1}; // gcd(1, a) = 1

  T operator ()(T a, T b) const noexcept
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

template <typename T, typename = typename std::enable_if<is_nonbool_integral<T>::value>::type>
struct lcm_impl
{
  using operator_category = binary_operator_tag;
  using operand_type = std::tuple<T, T>;

  static constexpr T neutral_elem {1}; // lcm(1, a) = a
  static constexpr T absorbing_elem {0}; // lcm(0, a) = 0

  AAL_INT_WCONVERSION_WCOMPARE_PUSH

  T operator ()(T a, T b) const noexcept
  {
    assert(!ioverflows::mul(a / gcd_impl<T> {}(a, b), b, std::numeric_limits<T>::max()) && "the lcm cannot be represented");
    return a / gcd_impl<T> {}(a, b) * b;
  }

  AAL_INT_WCONVERSION_WCOMPARE_POP
};

} // namespace detail

// class template representing operator gcd
// auto gcd = aal::op::gcd<int> {};
// int ans = gcd(3, 6);
template <typename T>
using gcd = detail::gcd_impl<T>;

// class template representing operator lcm
// auto lcm = aal::op::lcm<int> {};
// int ans = lcm(3, 18);
template <typename T>
using lcm = detail::lcm_impl<T>;

}} // namespace aal::op

#endif // AAL_SRC_MATH_OPERATOR_GCD_HPP
