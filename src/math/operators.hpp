#ifndef AAL_SRC_MATH_OPERATORS_HPP
#define AAL_SRC_MATH_OPERATORS_HPP

#include "overflow_detection.hpp"

namespace aal { namespace ops {

struct unary_operator_tag
{
};

struct binary_operator_tag
{
};

namespace details {

template <typename TOp, typename = void_t<typename TOp::category, typename TOp::operand_type>>
struct operator_traits_impl
{
  using category     = typename TOp::category;
  using operand_type = typename TOp::operand_type;
};

} // namespace details

template <typename TOp>
using operator_traits = details::operator_traits_impl<TOp>;

enum class mode
{
  floor,
  ceil
};

}} // namespace aal::ops

#endif // AAL_SRC_MATH_OPERATORS_HPP
