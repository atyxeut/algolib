#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_CONVERSION_HELPER_AS_INDEX_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_CONVERSION_HELPER_AS_INDEX_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/integral/basic-operation/conversion-helper/as_index.hpp */

#include "../../../../concept/integral.hpp"

namespace aal {

template <integral T>
[[nodiscard]] constexpr auto as_index(T n) noexcept
{
  return static_cast<std::size_t>(n);
}

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_CONVERSION_HELPER_AS_INDEX_HPP
