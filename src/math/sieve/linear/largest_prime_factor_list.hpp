#ifndef AAL_SRC_MATH_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP
#define AAL_SRC_MATH_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/sieve/linear/largest_prime_factor_list.hpp */

#include <vector>

#include "../../int-operation/conversion-helper/as_index.hpp"

namespace aal { namespace sieve { namespace linear {

// get the largest prime factor list (maxp[i]: the largest prime divisor of i)
// the behavior is undefined if maxp[0], maxp[1] are used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <typename T>
[[nodiscard]] constexpr auto maxp(const std::vector<T>& prime, const std::vector<T>& minp)
{
  std::vector<T> maxp(minp.size());

  for (T n = static_cast<T>(minp.size() - 1), i = 2; i <= n; ++i) {
    if (minp[as_index(i)] == i)
      maxp[as_index(i)] = i;
    for (T p : prime) {
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      auto composite = static_cast<limit_type>(i) * static_cast<limit_type>(p);
      if (composite > static_cast<limit_type>(n))
        break;
      maxp[as_index(composite)] = std::max(maxp[as_index(i)], p);
      if (i % p == 0)
        break;
    }
  }

  return maxp;
}

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP
