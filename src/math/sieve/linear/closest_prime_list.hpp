#ifndef AAL_SRC_MATH_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP
#define AAL_SRC_MATH_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/sieve/linear/closest_prime_list.hpp */

#include "../../int-operation/conversion-helper/as_index.hpp"
#include <vector>

namespace aal { namespace sieve { namespace linear {

// get the closest prime list (clp[i]: the largest prime <= i)
// the behavior is undefined if clp[0], clp[1] are used
// the behavior is undefined if the argument is not the actual minp array
template <typename T>
auto clp(const std::vector<T>& minp) -> std::vector<T>
{
  std::vector<T> clp(minp.size());

  for (T n = static_cast<T>(minp.size() - 1), i = 2; i <= n; ++i)
    clp[as_index(i)] = minp[as_index(i)] == i ? i : clp[as_index(i - 1)];

  return clp;
}

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_SIEVE_LINEAR_CLOSEST_PRIME_LIST_HPP
