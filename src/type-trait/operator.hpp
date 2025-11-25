#ifndef AAL_SRC_TYPE_TRAIT_OPERATOR_HPP
#define AAL_SRC_TYPE_TRAIT_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/type-trait/operator.hpp */

#include <tuple>

#include "logical.hpp"
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
       t_enable_if_t<std::is_same<typename T::operator_category, unary_operator_tag>>, enable_if_t<std::tuple_size<typename T::operand_type>::value == 1>,
       decltype(std::declval<T&>()(std::declval<typename std::tuple_element<0, typename T::operand_type>::type>()))
     >
> : std::true_type
{
};

} // namespace detail

template <typename T>
using is_unary_operator = detail::is_unary_operator_impl<T>;

namespace detail {

template <typename, typename, typename, typename = void>
struct is_binary_callable : std::false_type
{
};

template <typename TOp, typename T1, typename T2>
struct is_binary_callable<TOp, T1, T2, void_t<decltype(std::declval<TOp&>()(std::declval<T1>(), std::declval<T2>()))>> : std::true_type
{
};

template <typename, typename = void>
struct is_binary_operator_impl : std::false_type
{
};

template <typename T>
struct is_binary_operator_impl<
  T, void_t<
       t_enable_if_t<std::is_same<typename T::operator_category, binary_operator_tag>>, enable_if_t<std::tuple_size<typename T::operand_type>::value == 2>,
       t_enable_if_t<disjunction<
         is_binary_callable<T, typename std::tuple_element<0, typename T::operand_type>::type, typename std::tuple_element<1, typename T::operand_type>::type>,
         is_binary_callable<T, typename std::tuple_element<1, typename T::operand_type>::type, typename std::tuple_element<0, typename T::operand_type>::type>
       >>
     >
> : std::true_type
{
};

} // namespace detail

template <typename T>
using is_binary_operator = detail::is_binary_operator_impl<T>;

namespace detail {

template <typename, typename = void>
struct is_multipliable_impl : std::false_type
{
};

template <typename T>
struct is_multipliable_impl<
  T, void_t<
       t_enable_if_t<std::is_same<decltype(std::declval<T>() * std::declval<T>()), T>>,
       t_enable_if_t<std::is_same<decltype(std::declval<T&>() *= std::declval<T>()), T&>>
     >
> : std::true_type
{
};

} // namespace detail

template <typename T>
using is_multipliable = detail::is_multipliable_impl<T>;

namespace detail {

template <typename, typename, typename = void>
struct is_weakly_equality_comparable_with_impl : std::false_type
{
};

template <typename T1, typename T2>
struct is_weakly_equality_comparable_with_impl<
  T1, T2,
  void_t<
    t_enable_if_t<std::is_convertible<decltype(std::declval<T1&>() == std::declval<T2&>()), bool>>,
    t_enable_if_t<std::is_convertible<decltype(std::declval<T1&>() != std::declval<T2&>()), bool>>,
    t_enable_if_t<std::is_convertible<decltype(std::declval<T2&>() == std::declval<T1&>()), bool>>,
    t_enable_if_t<std::is_convertible<decltype(std::declval<T2&>() != std::declval<T1&>()), bool>>
  >
> : std::true_type
{
};

} // namespace detail

template <typename T1, typename T2>
using is_weakly_equality_comparable_with = detail::is_weakly_equality_comparable_with_impl<T1, T2>;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_OPERATOR_HPP
