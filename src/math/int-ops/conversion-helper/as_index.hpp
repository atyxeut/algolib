#ifndef AAL_SRC_MATH_INT_OPS_CONVERSION_HELPER_AS_INDEX_HPP
#define AAL_SRC_MATH_INT_OPS_CONVERSION_HELPER_AS_INDEX_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-ops/conversion-helper/as_index.hpp */

#include "../../../concepts/integral.hpp"

namespace aal {

template <integral T>
[[nodiscard]] constexpr auto as_index(T n) noexcept
{
  return static_cast<std::size_t>(n);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_CONVERSION_HELPER_AS_INDEX_HPP
