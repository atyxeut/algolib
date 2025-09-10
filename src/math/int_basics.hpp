#ifndef AAL_SRC_MATH_INT_BASICS_HPP
#define AAL_SRC_MATH_INT_BASICS_HPP

#include "overflow_detection.hpp"

namespace aal {

template <typename T>
constexpr auto iabs(T n) noexcept -> ::aal::t_enable_if_t<::aal::is_unsigned<T>, T>
{
  return n;
}

template <typename T>
constexpr auto iabs(T n) noexcept -> typename ::aal::t_enable_if_t<::aal::is_signed<T>, ::aal::make_unsigned<T>>::type
{
  return n >= 0 ? n : ~static_cast<::aal::make_unsigned_t<T>>(n) + 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_BASICS_HPP
