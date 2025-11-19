#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_MILLER_RABIN_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_MILLER_RABIN_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/integral/basic-operation/is-prime/miller_rabin.hpp */

#include "../../../../concept/integral.hpp"

namespace aal::is_prime {

template <nonbool_integral T>
[[nodiscard]] constexpr bool miller_rabin(T n) noexcept
{
  if (n < 2)
    return false;

  return true;
}

} // namespace aal::is_prime

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_MILLER_RABIN_HPP
