#ifndef AAL_SRC_LIB_MATH_OPERATOR_IEXP_POW_INCLUDE_HPP
#define AAL_SRC_LIB_MATH_OPERATOR_IEXP_POW_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/operator/iexp_pow/include.hpp */

#include "../../../../fundamental/type_trait/integral.hpp"
#include "../../../../fundamental/type_trait/operator.hpp"

namespace aal::op {

template <multipliable T, nonbool_unsigned TExponent> requires std::equality_comparable<T>
struct iexp_pow
{
  using operator_category = binary_operator_tag;
  using operand_type = std::tuple<T, TExponent>;

  // a multipliable type must provide a constructor that transform 1 into the multiplication neutral element,
  //   otherwise, the behavior is undefined
  static constexpr T neutral_element {1};

  [[nodiscard]] static constexpr T operator ()(T a, TExponent exp) noexcept
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

} // namespace aal::op

#endif // AAL_SRC_LIB_MATH_OPERATOR_IEXP_POW_INCLUDE_HPP
