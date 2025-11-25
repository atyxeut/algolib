#ifndef AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_DIVISOR_HPP
#define AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_DIVISOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/integral/arithmetic-function/divisor.hpp */

// see https://en.wikipedia.org/wiki/Divisor_function#Formulas_at_prime_powers for extra information

#include "../../../macro/warning.hpp"
#include "../basic-operation/pow.hpp"

namespace aal { namespace arith_func {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

template <int x = 1, typename T>
auto sigma(T n) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, T>::type
{
  assert(n > 0 && "argument must be positive");

  T ans = 0;
  for (T i = 1; i <= n / i; ++i) {
    if (n % i == 0) {
      assert(!ioverflows::add(ans, ipow(i, x), std::numeric_limits<T>::max()) && "the result cannot be represented");
      ans += ipow(i, x);
      if (n / i != i) {
        assert(!ioverflows::add(ans, ipow(n / i, x), std::numeric_limits<T>::max()) && "the result cannot be represented");
        ans += ipow(n / i, x);
      }
    }
  }
  return ans;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

}} // namespace aal::arith_func

#endif // AAL_SRC_MATH_INTEGRAL_ARITHMETIC_FUNCTION_DIVISOR_HPP
