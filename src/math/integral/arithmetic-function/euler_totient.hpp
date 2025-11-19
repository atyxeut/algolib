#ifndef AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_EULER_TOTIENT_HPP
#define AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_EULER_TOTIENT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/integral/arithmetic-function/euler_totient.hpp */

#include <cassert>

#include "../../../concept/integral.hpp"

// see https://en.wikipedia.org/wiki/Euler%27s_totient_function#Computing_Euler's_totient_function for extra information

namespace aal { namespace arith_func {

template <nonbool_integral T>
[[nodiscard]] constexpr auto euler_totient(T n) noexcept
{
  assert(n > 0 && "argument must be positive");

  T ans = n;
  for (T i = 2; i <= n / i; ++i) {
    if (n % i == 0)
      ans = ans / i * (i - 1);
    while (n % i == 0)
      n /= i;
  }
  return n > 1 ? ans / n * (n - 1) : ans;
}

}} // namespace aal::arith_func

#endif // AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_EULER_TOTIENT_HPP
