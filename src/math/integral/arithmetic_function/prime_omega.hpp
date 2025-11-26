#ifndef AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_PRIME_OMEGA_HPP
#define AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_PRIME_OMEGA_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/arithmetic_function/prime_omega.hpp */

// see https://en.wikipedia.org/wiki/Prime_omega_function#Properties_and_relations for extra information

#include <cassert>

#include "../../../concept/integral.hpp"

namespace aal::arith_func {

template <nonbool_integral T>
[[nodiscard]] constexpr auto little_omega(T n) noexcept
{
  assert(n > 0 && "argument must be positive");

  T ans = 0;
  for (T i = 2; i <= n / i; ++i) {
    ans += n % i == 0;
    while (n % i == 0)
      n /= i;
  }
  return ans += n > 1;
}

template <nonbool_integral T>
[[nodiscard]] constexpr auto big_omega(T n) noexcept
{
  assert(n > 0 && "argument must be positive");

  T ans = 0;
  for (T i = 2; i <= n / i; ++i) {
    while (n % i == 0) {
      ++ans;
      n /= i;
    }
  }
  return ans += n > 1;
}

} // namespace aal::arith_func

#endif // AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_PRIME_OMEGA_HPP
