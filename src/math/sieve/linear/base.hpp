#ifndef AAL_SRC_MATH_SIEVE_LINEAR_BASE_HPP
#define AAL_SRC_MATH_SIEVE_LINEAR_BASE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/sieve/linear/base.hpp */

#include "../../../type-traits/integral.hpp"
#include <cassert>
#include <tuple>
#include <vector>

// see linear.md for extra information

namespace aal { namespace sieve { namespace linear {

// get the prime list and the smallest prime factor list (minp[i]: the smallest prime divisor of i, minp[i] = i: i is a prime, otherwise not)
// the behavior is undefined if minp[0], minp[1] are used
template <typename T>
auto base(T n) -> typename std::enable_if<is_nonbool_integral<T>::value, std::tuple<std::vector<T>, std::vector<T>>>::type
{
  assert(n > 0 && "the argument must be positive");

  std::vector<T> prime;
  std::vector<T> minp(n + 1);

  for (T i = 2; i <= n; ++i) {
    if (!minp[i]) {
      prime.push_back(i);
      minp[i] = i;
    }
    for (T p : prime) {
      // i * p may still overflow, but it takes forever to reach such a case
      auto composite = static_cast<make_unsigned_t<make_larger_width_t<T>>>(i) * p;
      if (composite > n)
        break;
      minp[composite] = p;
      if (i % p == 0)
        break;
    }
  }

  return {prime, minp};
}

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_SIEVE_LINEAR_BASE_HPP
