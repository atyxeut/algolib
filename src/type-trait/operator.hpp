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

namespace detail {

// follow the STL design, provide an empty class for invalid types, make it friendly to tag dispatch
template <typename T, typename = void>
struct operator_traits_impl
{
};

template <typename T>
struct operator_traits_impl<T, std::void_t<typename T::operator_category, typename T::operand_type>>
{
  using operator_category = T::operator_category;
  using operand_type = T::operand_type;
};

} // namespace detail

template <typename T>
struct operator_traits : detail::operator_traits_impl<T>
{
};

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_OPERATOR_HPP
