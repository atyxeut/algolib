#ifndef AAL_SRC_MATH_INT_OPS_FACTORIZATION_ALL_HPP
#define AAL_SRC_MATH_INT_OPS_FACTORIZATION_ALL_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/int-ops/factorization/all.hpp */

#include "../../../type-traits/integral.hpp"
#include <cassert>
#include <vector>

namespace aal { namespace get_divisor {

// get all unique divisors of an integer
// std::vector<int> ret = aal::get_divisor::all(36);
// ret is [1, 2, 3, 4, 6, 9, 12, 18, 36]
template <typename T>
auto all(T n) -> typename std::enable_if<is_nonbool_integral<T>::value, std::vector<T>>::type
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

}} // namespace aal::get_divisor

#endif // AAL_SRC_MATH_INT_OPS_FACTORIZATION_ALL_HPP
