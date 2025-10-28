#ifndef AAL_SRC_MATH_SIEVE_ERATOSTHENES_HPP
#define AAL_SRC_MATH_SIEVE_ERATOSTHENES_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/sieve/eratosthenes.hpp */

#include "../../type-traits/integral.hpp"
#include <cassert>
#include <vector>

namespace aal { namespace sieve {

// get a not_prime list (not_prime[i] = true/false means i is not/is a prime)
// the behavior is undefined if not_prime[0], not_prime[1] are used
template <typename T>
auto eratosthenes(T n) -> std::vector<bool>
{
  static_assert(is_nonbool_integral<T>::value, "argument must be integer");
  assert(n > 0 && "argument must be positive");

  std::vector<bool> not_prime(n + 1);
  for (T i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      // every multiple < i^2 is already marked
      // for example, if i = 7, then 2i, 3i, 4i, 5i, 6i are already marked by smaller primes 2, 3, 2, 5, 2
      // i^2 may still overflow, but it takes forever to reach such a case
      for (auto j = static_cast<make_larger_width_t<T>>(i) * i; j <= n; j += i)
        not_prime[j] = true;
    }
  }
  return not_prime;
}

}} // namespace aal::sieve

#endif // AAL_SRC_MATH_SIEVE_ERATOSTHENES_HPP
