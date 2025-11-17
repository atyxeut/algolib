#ifndef AAL_SRC_CONCEPT_OPERATOR_HPP
#define AAL_SRC_CONCEPT_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concept/operator.hpp */

namespace aal {

template <typename T>
concept math_operator = requires {
  typename T::operator_category;
  typename T::operand_type;
};

template <typename T>
concept unary_operator = true;

template <typename T>
concept binary_operator = true;

} // namespace aal

#endif // AAL_SRC_CONCEPT_OPERATOR_HPP
