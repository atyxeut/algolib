#ifndef AAL_SRC_TYPE_TRAIT_OPERATOR_HPP
#define AAL_SRC_TYPE_TRAIT_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-trait/operator.hpp */

#include "sfinae.hpp"

namespace aal {

struct unary_operator_tag
{
};

struct binary_operator_tag
{
};

namespace detail {

// follow the STL design, provide an empty class for invalid types, make it friendly to tag dispatch
template <typename, typename = void>
struct operator_traits_impl
{
};

template <typename T>
struct operator_traits_impl<T, void_t<typename T::operator_category, typename T::operand_type>>
{
  using operator_category = typename T::operator_category;
  using operand_type = typename T::operand_type;
};

} // namespace detail

template <typename T>
struct operator_traits : detail::operator_traits_impl<T>
{
};

namespace detail {

template <typename, typename = void>
struct is_unary_operator_impl : std::false_type
{
};

template <typename T>
struct is_unary_operator_impl<
  T, void_t<
       t_enable_if_t<std::is_same<typename T::operator_category, unary_operator_tag>>,
       t_enable_if_t<std::is_same<decltype(std::declval<T&>()(std::declval<typename T::operand_type>())), typename T::operand_type>>
     >
> : std::true_type
{
};

} // namespace detail

template <typename T>
using is_unary_operator = detail::is_unary_operator_impl<T>;

namespace detail {

template <typename, typename = void>
struct is_binary_operator_impl : std::false_type
{
};

template <typename T>
struct is_binary_operator_impl<
  T,
  void_t<
    t_enable_if_t<std::is_same<typename T::operator_category, binary_operator_tag>>,
    t_enable_if_t<
      std::is_same<decltype(std::declval<T&>()(std::declval<typename T::operand_type>(), std::declval<typename T::operand_type>())), typename T::operand_type>
    >
  >
> : std::true_type
{
};

} // namespace detail

template <typename T>
using is_binary_operator = detail::is_binary_operator_impl<T>;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_OPERATOR_HPP
