#ifndef AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_OPERATOR_HPP
#define AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_OPERATOR_HPP

#include <concepts>
#include <tuple>

#include "enum.hpp"

namespace aal {

namespace op {

enum class property
{
  associative = 1 << 0,
  commutative = 1 << 1
};

} // namespace op

template <>
struct is_enum_flag<op::property> : std::true_type
{
};

struct unary_operator_tag
{
};

struct binary_operator_tag
{
};

// follow the STL design, provide an empty class for invalid types, make it friendly to tag dispatch
template <typename>
struct operator_traits
{
};

template <typename T> requires requires {
  typename T::operator_category;
  typename T::operand_type;
}
struct operator_traits<T>
{
  using operator_category = T::operator_category;
  using operand_type = T::operand_type;
};

template <typename T>
concept unary_operator = requires(const T op, std::tuple_element_t<0, typename T::operand_type> a) {
  requires std::same_as<typename T::operator_category, unary_operator_tag>;
  requires (std::tuple_size_v<typename T::operand_type> == 1);
  { op(a) };
};

template <typename T>
concept binary_operator = requires(const T op, std::tuple_element_t<0, typename T::operand_type> a, std::tuple_element_t<1, typename T::operand_type> b) {
  requires std::same_as<typename T::operator_category, binary_operator_tag>;
  requires (std::tuple_size_v<typename T::operand_type> == 2);
  requires (requires { op(a, b); } || requires { op(b, a); });
};

template <typename T>
concept multipliable = requires(T a, T b) {
  { a * b } -> std::same_as<T>;
  { a *= b } -> std::same_as<T&>;
};

} // namespace aal

#endif // AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_OPERATOR_HPP
