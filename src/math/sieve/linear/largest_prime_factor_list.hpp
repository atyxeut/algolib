#ifndef AAL_SRC_MATH_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP
#define AAL_SRC_MATH_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/sieve/linear/largest_prime_factor_list.hpp */

#include "../../../type-traits/integral.hpp"
#include <vector>

namespace aal { namespace sieve { namespace linear {

// get the largest prime factor list (maxp[i]: the largest prime divisor of i)
// the behavior is undefined if maxp[0], maxp[1] are used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <typename T>
auto maxp(const std::vector<T>& prime, const std::vector<T>& minp) -> std::vector<T>
{
  T n = minp.size() - 1;

  std::vector<T> maxp(n + 1);

  for (T i = 2; i <= n; ++i) {
    if (minp[i] == i)
      maxp[i] = i;
    for (T p : prime) {
      auto composite = static_cast<make_unsigned_t<make_larger_width_t<T>>>(i) * p;
      if (composite > n)
        break;
      maxp[composite] = std::max(maxp[i], p);
      if (i % p == 0)
        break;
    }
  }

  return maxp;
}

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP
