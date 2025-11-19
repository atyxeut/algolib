#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_ALL_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_ALL_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/integral/basic-operation/factorization/all.hpp */

#include <cassert>
#include <vector>

#include "../../../../concept/integral.hpp"

namespace aal::get_divisor {

// get all unique divisors of an integer
// std::vector<int> ret = aal::get_divisor::all(36);
// ret is [1, 2, 3, 4, 6, 9, 12, 18, 36]
template <nonbool_integral T>
[[nodiscard]] constexpr auto all(T n)
{
  assert(n > 0 && "argument must be positive");

  // divisors are in pairs, let n = a * b and a <= b, then a <= sqrt(n) <= b, we only need to find all possible a, then calculate b
  std::vector<T> info;
  for (T i = 1; i <= n / i; ++i)
    if (n % i == 0)
      info.push_back(i);

  for (auto it = info.rbegin(), it_end = info.rend(); it != it_end; ++it) {
    T another = n / *it;
    if (another != *it)
      info.push_back(another);
  }
  return info;
}

} // namespace aal::get_divisor

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_ALL_HPP
