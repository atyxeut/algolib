#ifndef AAL_SRC_CONCEPT_INTEGRAL_HPP
#define AAL_SRC_CONCEPT_INTEGRAL_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/concept/integral.hpp */

#include <concepts>

#include "../type_trait/integral.hpp"

namespace aal {

template <typename T>
concept integral = is_integral_v<T>;

template <typename T>
concept standard_integral = is_standard_integral_v<T>;

template <typename T>
concept nonbool_integral = is_nonbool_integral_v<T>;

template <typename T>
concept signed_integral = integral<T> && is_signed_v<T>;

template <typename T>
concept unsigned_integral = integral<T> && !signed_integral<T>;

template <typename T>
concept nonbool_unsigned = nonbool_integral<T> && unsigned_integral<T>;

} // namespace aal

#endif // AAL_SRC_CONCEPT_INTEGRAL_HPP
