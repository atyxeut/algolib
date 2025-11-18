#ifndef AAL_SRC_MATH_INT_OPERATION_CONVERSION_HELPER_AS_INDEX_HPP
#define AAL_SRC_MATH_INT_OPERATION_CONVERSION_HELPER_AS_INDEX_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-operation/conversion-helper/as_index.hpp */

#include "../../../type-trait/integral.hpp"

namespace aal {

template <typename T>
constexpr auto as_index(T n) noexcept -> typename std::enable_if<is_integral<T>::value, std::size_t>::type
{
  return static_cast<std::size_t>(n);
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPERATION_CONVERSION_HELPER_AS_INDEX_HPP
