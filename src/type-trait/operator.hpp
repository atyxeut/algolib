#ifndef AAL_SRC_TYPE_TRAIT_OPERATOR_HPP
#define AAL_SRC_TYPE_TRAIT_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/type-trait/operator.hpp */

#include <type_traits>

namespace aal {

struct unary_operator_tag
{
};

struct binary_operator_tag
{
};

template <typename T>
struct operator_traits_base
{
  using operator_category = typename T::operator_category;
  using operand_type = typename T::operand_type;
};

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_OPERATOR_HPP
