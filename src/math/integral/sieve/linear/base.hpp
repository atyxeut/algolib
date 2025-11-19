#ifndef AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_BASE_HPP
#define AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_BASE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/integral/sieve/linear/base.hpp */

#include <cassert>
#include <utility>
#include <vector>

#include "../../basic-operation/conversion-helper/as_index.hpp"

// see note.md for extra information

namespace aal { namespace sieve { namespace linear {

// get the prime list and the smallest prime factor list (minp[i]: the smallest prime divisor of i, minp[i] = i: i is a prime, otherwise not)
// the behavior is undefined if minp[0], minp[1] are used
template <typename T>
auto base(T n) -> typename std::enable_if<is_nonbool_integral<T>::value, std::pair<std::vector<T>, std::vector<T>>>::type
{
  assert(n > 0 && "the argument must be positive");

  std::vector<T> prime;
  std::vector<T> minp(as_index(n) + 1);

  for (T i = 2; i <= n; ++i) {
    if (!minp[as_index(i)]) {
      prime.push_back(i);
      minp[as_index(i)] = i;
    }
    for (T p : prime) {
      // i * p may still overflow, but it takes forever to reach such a case
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      auto composite = static_cast<limit_type>(i) * static_cast<limit_type>(p);
      if (composite > static_cast<limit_type>(n))
        break;
      minp[as_index(composite)] = p;
      if (i % p == 0)
        break;
    }
  }

  return {prime, minp};
}

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_BASE_HPP
