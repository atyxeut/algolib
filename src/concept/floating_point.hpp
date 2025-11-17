#ifndef AAL_SRC_CONCEPT_FLOATING_POINT_HPP
#define AAL_SRC_CONCEPT_FLOATING_POINT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concept/floating_point.hpp */

#include "../type-trait/floating_point.hpp"

namespace aal {

template <typename T>
concept floating_point = is_floating_point_v<T>;

template <typename T>
concept standard_floating_point = is_standard_floating_point_v<T>;

} // namespace aal

#endif // AAL_SRC_CONCEPT_FLOATING_POINT_HPP
