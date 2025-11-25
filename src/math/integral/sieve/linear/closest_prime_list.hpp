#ifndef AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP
#define AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/integral/sieve/linear/closest_prime_list.hpp */

#include <vector>

#include "../../../../macro/warning.hpp"

namespace aal { namespace sieve { namespace linear {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

// get the closest prime list (clp[i]: the largest prime <= i)
// the behavior is undefined if clp[0], clp[1] are used
// the behavior is undefined if the argument is not the actual minp array
template <typename T>
auto clp(const std::vector<T>& minp) -> std::vector<T>
{
  std::vector<T> clp(minp.size());

  for (T n = minp.size() - 1, i = 2; i <= n; ++i)
    clp[i] = minp[i] == i ? i : clp[i - 1];
  return clp;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP
