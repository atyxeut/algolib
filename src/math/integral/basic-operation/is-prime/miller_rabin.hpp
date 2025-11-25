#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_MILLER_RABIN_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_MILLER_RABIN_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/integral/basic-operation/is-prime/miller_rabin.hpp */

#include "../../../../type-trait/integral.hpp"

namespace aal { namespace is_prime {

template <typename T>
auto miller_rabin(T n) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, bool>::type
{
  if (n < 2)
    return false;

  return true;
}

}} // namespace aal::is_prime

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_IS_PRIME_MILLER_RABIN_HPP
