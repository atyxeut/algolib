#ifndef AAL_SRC_MATH_OPERATOR_IPOW_INCLUDE_HPP
#define AAL_SRC_MATH_OPERATOR_IPOW_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/operator/ipow/include.hpp */

#include "../../../type-trait/integral.hpp"
#include "../../../type-trait/operator.hpp"

namespace aal { namespace op {

namespace detail {

template <
  typename T, typename TExponent,
  typename = t_enable_if_t<conjunction<is_multipliable<T>, is_weakly_equality_comparable_with<T, T>, is_nonbool_unsigned<TExponent>>>
>
struct ipow_impl
{
  using operator_category = binary_operator_tag;
  using operand_type = std::tuple<T, TExponent>;

  // a multipliable type must provide a constructor that transform 1 into the multiplication neutral element,
  //   otherwise, the behavior is undefined
  static constexpr T neutral_element {1};

  T operator ()(T a, TExponent exp) const noexcept
  {
    if (exp == 0 || a == neutral_element)
      return neutral_element;

    T ans = neutral_element;
    while (true) {
      if (exp & 1)
        ans *= a;
      exp >>= 1;
      if (exp == 0)
        break;
      a *= a;
    }
    return ans;
  }
};

} // namespace detail

template <typename T, typename TExponent>
using ipow = detail::ipow_impl<T, TExponent>;

}} // namespace aal::op

#endif // AAL_SRC_MATH_OPERATOR_IPOW_INCLUDE_HPP
