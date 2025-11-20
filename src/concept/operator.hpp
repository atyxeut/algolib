#ifndef AAL_SRC_CONCEPT_OPERATOR_HPP
#define AAL_SRC_CONCEPT_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concept/operator.hpp */

#include <concepts>
#include <tuple>

#include "../type-trait/operator.hpp"

namespace aal {

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

#endif // AAL_SRC_CONCEPT_OPERATOR_HPP
