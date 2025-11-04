#ifndef AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_EULER_TOTIENT_HPP
#define AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_EULER_TOTIENT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/arithmetic-functions/euler_totient.hpp */

#include "../../macros/constexpr.hpp"
#include "../../type-traits/integral.hpp"
#include <cassert>

// see https://en.wikipedia.org/wiki/Euler%27s_totient_function#Computing_Euler's_totient_function for extra information

namespace aal { namespace arith_func {

template <typename T>
AAL_CONSTEXPR14 auto euler_totient(T n) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, T>::type
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

#endif // AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_EULER_TOTIENT_HPP
