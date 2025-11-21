#ifndef AAL_SRC_MATH_OPERATOR_IPOW_INCLUDE_HPP
#define AAL_SRC_MATH_OPERATOR_IPOW_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/operator/ipow/include.hpp */

#include <cassert>

#include "../../../concept/operator.hpp"
#include "../../integral/basic-operation/overflow-detection/general.hpp"

namespace aal::op {

template <multipliable T, nonbool_unsigned TExponent> requires std::equality_comparable<T>
struct ipow
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
      if (exp & 1) {
        if constexpr (integral<T>) // user defined types should assert overflow directly inside the operator overloads
          assert(ioverflows::general::mul<T>(ans, a) && "the result cannot be represented");
        ans *= a;
      }
      exp >>= 1;
      if (exp == 0)
        break;
      if constexpr (integral<T>)
        assert(ioverflows::general::mul<T>(a, a) && "the result cannot be represented");
      a *= a;
    }
    return ans;
  }
};

} // namespace aal::op

#endif // AAL_SRC_MATH_OPERATOR_IPOW_INCLUDE_HPP
