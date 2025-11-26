#ifndef AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/sieve/linear/closest_prime_list.hpp */

#include <vector>

#include "../../../../../fundamental/macro/warning.hpp"

namespace aal::sieve::linear {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

// get the closest prime list (clp[i]: the largest prime <= i)
// the behavior is undefined if clp[0], clp[1] are used
// the behavior is undefined if the argument is not the actual minp array
template <typename T>
[[nodiscard]] constexpr auto clp(const std::vector<T>& minp)
{
  std::vector<T> clp(minp.size());

  for (T n = minp.size() - 1, i = 2; i <= n; ++i)
    clp[i] = minp[i] == i ? i : clp[i - 1];
  return clp;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace aal::sieve::linear

#endif // AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP
