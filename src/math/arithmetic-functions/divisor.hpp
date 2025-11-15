#ifndef AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_DIVISOR_HPP
#define AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_DIVISOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/arithmetic-functions/divisor.hpp */

#include "../int-ops/pow/include.hpp"

// see https://en.wikipedia.org/wiki/Divisor_function#Formulas_at_prime_powers for extra information

namespace aal { namespace arith_func {

template <int x = 1, nonbool_integral T>
[[nodiscard]] constexpr auto sigma(T n) noexcept
{
  assert(n > 0 && "argument must be positive");

  T ans = 0;
  for (T i = 1; i <= n / i; ++i) {
    if (n % i == 0) {
      assert(!iadd_overflows<T>(ans, ipow(i, x)) && "the result cannot be represented");
      ans += ipow(i, x);
      if (n / i != i) {
        assert(!iadd_overflows<T>(ans, ipow(n / i, x)) && "the result cannot be represented");
        ans += ipow(n / i, x);
      }
    }
  }
  return ans;
}

}} // namespace aal::arith_func

#endif // AAL_SRC_MATH_ARITHMETIC_FUNCTIONS_DIVISOR_HPP
