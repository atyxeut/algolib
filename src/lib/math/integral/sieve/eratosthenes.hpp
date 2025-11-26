#ifndef AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_ERATOSTHENES_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_ERATOSTHENES_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/sieve/eratosthenes.hpp */

#include <vector>

#include "../../../../fundamental/concept/integral.hpp"
#include "../../../../fundamental/macro/warning.hpp"

namespace aal::sieve {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

// get a not_prime list (not_prime[i] = true/false means i is not/is a prime)
// the behavior is undefined if not_prime[0], not_prime[1] are used
template <nonbool_integral T>
[[nodiscard]] constexpr auto eratosthenes(T n)
{
  assert(n > 0 && "argument must be positive");

  std::vector<bool> not_prime(n + 1);
  for (T i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      // every multiple < i^2 is already marked
      // for example, if i = 7, then 2i, 3i, 4i, 5i, 6i are already marked by smaller primes 2, 3, 2, 5, 2
      // i^2 may still overflow, but it takes forever to reach such a case
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      for (auto j = static_cast<limit_type>(i) * i; j <= n; j += i)
        not_prime[j] = true;
    }
  }
  return not_prime;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace aal::sieve

#endif // AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_ERATOSTHENES_HPP
