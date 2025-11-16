#ifndef AAL_SRC_CONCEPTS_OPERATOR_HPP
#define AAL_SRC_CONCEPTS_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concepts/operator.hpp */

namespace aal {

template <typename T>
concept optr = requires {
  typename T::operator_category;
  typename T::operand_type;
};

} // namespace aal

#endif // AAL_SRC_CONCEPTS_OPERATOR_HPP
