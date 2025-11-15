#ifndef AAL_SRC_MATH_OPERATOR_TRAITS_HPP
#define AAL_SRC_MATH_OPERATOR_TRAITS_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/operator/traits.hpp */

#include "../../concepts/operator.hpp"
#include "categories.hpp"

namespace aal { namespace op {

template <optr T>
struct operator_traits_base
{
  // clang-format off
  using category     = typename T::category;
  using operand_type = typename T::operand_type;
  // clang-format on
};

}} // namespace aal::op

#endif // AAL_SRC_MATH_OPERATOR_TRAITS_HPP
