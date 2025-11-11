#ifndef AAL_SRC_MATH_INT_OPS_FACTORIZATION_PRIME_HPP
#define AAL_SRC_MATH_INT_OPS_FACTORIZATION_PRIME_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/factorization/prime.hpp */

#include "../../../type-traits/integral.hpp"
#include <array>
#include <cassert>
#include <vector>

namespace aal { namespace get_divisor {

// get the prime factorization of an integer n in O(sqrt(n)) time
// int n = 36;
// std::vector<std::array<int, 2>> ret = aal::get_divisor::prime(n);
// ret is [[2, 2], [3, 2]]
template <typename T>
auto prime(T n) -> typename std::enable_if<is_nonbool_integral<T>::value, std::vector<std::array<T, 2>>>::type
{
  assert(n > 0 && "argument must be positive");

  // if there exists a prime p of n that is > sqrt(n), then its the only, otherwise the total product exceeds n
  std::vector<std::array<T, 2>> info;
  for (T i = 2; i <= n / i; ++i) {
    if (n % i == 0)
      info.push_back({i, 0});
    for (; n % i == 0; n /= i)
      ++info.back()[1];
  }
  if (n > 1)
    info.push_back({n, 1});
  return info;
}

}} // namespace aal::get_divisor

#endif // AAL_SRC_MATH_INT_OPS_FACTORIZATION_PRIME_HPP
