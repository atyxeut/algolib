#ifndef AAL_SRC_CONCEPTS_FLOATING_POINT_HPP
#define AAL_SRC_CONCEPTS_FLOATING_POINT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concepts/floating_point.hpp */

#include "../type-traits/floating_point.hpp"

namespace aal {

template <typename T>
concept floating_point = is_floating_point_v<T>;

template <typename T>
concept standard_floating_point = is_standard_floating_point_v<T>;

} // namespace aal

#endif // AAL_SRC_CONCEPTS_FLOATING_POINT_HPP
