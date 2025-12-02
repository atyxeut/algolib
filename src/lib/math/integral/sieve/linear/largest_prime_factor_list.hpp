#ifndef AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/sieve/linear/largest_prime_factor_list.hpp */

#include <vector>

#include "../../../../../fundamental/macro/warning.hpp"
#include "../../../../../fundamental/type_trait/integral.hpp"

namespace aal::sieve::linear {

AAL_INT_WCONVERSION_WCOMPARE_PUSH()

// get the largest prime factor list (maxp[i]: the largest prime divisor of i)
// the behavior is undefined if maxp[0], maxp[1] are used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <typename T>
[[nodiscard]] constexpr auto maxp(const std::vector<T>& prime, const std::vector<T>& minp)
{
  std::vector<T> maxp(minp.size());

  for (T n = minp.size() - 1, i = 2; i <= n; ++i) {
    if (minp[i] == i)
      maxp[i] = i;
    for (T p : prime) {
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      auto composite = static_cast<limit_type>(i) * p;
      if (composite > n)
        break;
      maxp[composite] = std::max(maxp[i], p);
      if (i % p == 0)
        break;
    }
  }
  return maxp;
}

AAL_INT_WCONVERSION_WCOMPARE_POP()

} // namespace aal::sieve::linear

#endif // AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_LARGEST_PRIME_FACTOR_LIST_HPP
