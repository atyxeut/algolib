#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic-operation/factorization/prime.hpp */

#include <array>
#include <cassert>
#include <vector>

#include "../../../../concept/integral.hpp"

namespace aal::get_divisor {

// get the prime factorization of an integer n in O(sqrt(n)) time
// int n = 36;
// std::vector<std::array<int, 2>> ret = aal::get_divisor::prime(n);
// ret is [[2, 2], [3, 2]]
template <nonbool_integral T>
[[nodiscard]] constexpr auto prime(T n)
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

} // namespace aal::get_divisor

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_HPP
