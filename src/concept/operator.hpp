#ifndef AAL_SRC_CONCEPT_OPERATOR_HPP
#define AAL_SRC_CONCEPT_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concept/operator.hpp */

#include "../type-trait/operator.hpp"
#include <concepts>

namespace aal {

template <typename T>
concept unary_operator = std::same_as<typename operator_traits<T>::operator_category, unary_operator_tag> && requires(const T op, T::operand_type r) {
  { op(r) } -> std::same_as<typename T::operand_type>;
};

template <typename T>
concept binary_operator = std::same_as<typename operator_traits<T>::operator_category, binary_operator_tag> &&
                          requires(const T op, T::operand_type l, T::operand_type r) {
                            { op(l, r) } -> std::same_as<typename T::operand_type>;
                          };

} // namespace aal

#endif // AAL_SRC_CONCEPT_OPERATOR_HPP
