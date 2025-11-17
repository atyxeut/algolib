#ifndef AAL_SRC_CONCEPT_OPERATOR_HPP
#define AAL_SRC_CONCEPT_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concept/operator.hpp */

#include "../type-trait/operator.hpp"
#include <concepts>

namespace aal {

template <typename T>
concept operator_traits_instantiatable = requires {
  typename T::operator_category;
  typename T::operand_type;
};

template <typename T>
concept unary_operator = operator_traits_instantiatable<T> && requires(const T op, T::operand_type operand) {
  { op(operand) } -> std::same_as<typename T::operand_type>;
};

template <typename T>
concept binary_operator = operator_traits_instantiatable<T> && requires(const T op, T::operand_type l, T::operand_type r) {
  { op(l, r) } -> std::same_as<typename T::operand_type>;
};

} // namespace aal

#endif // AAL_SRC_CONCEPT_OPERATOR_HPP
