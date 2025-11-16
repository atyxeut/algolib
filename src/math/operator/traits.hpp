#ifndef AAL_SRC_MATH_OPERATOR_TRAITS_HPP
#define AAL_SRC_MATH_OPERATOR_TRAITS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/operator/traits.hpp */

#include "categories.hpp"

namespace aal { namespace op {

template <typename TOp>
struct operator_traits_base
{
  using operator_category = typename TOp::operator_category;
  using operand_type = typename TOp::operand_type;
};

}} // namespace aal::op

#endif // AAL_SRC_MATH_OPERATOR_TRAITS_HPP
