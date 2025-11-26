#ifndef AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_BASE_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_BASE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/sieve/linear/base.hpp */

#include <utility>
#include <vector>

#include "../../../../../fundamental/concept/integral.hpp"
#include "../../../../../fundamental/macro/warning.hpp"

namespace aal::sieve::linear {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

// get the prime list and the smallest prime factor list (minp[i]: the smallest prime divisor of i, minp[i] = i: i is a prime, otherwise not)
// the behavior is undefined if minp[0], minp[1] are used
template <nonbool_integral T>
[[nodiscard]] constexpr auto base(T n)
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
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      auto composite = static_cast<limit_type>(i) * p;
      if (composite > n)
        break;
      minp[composite] = p;
      if (i % p == 0)
        break;
    }
  }
  return std::make_pair(prime, minp);
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace aal::sieve::linear

#endif // AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_BASE_HPP
