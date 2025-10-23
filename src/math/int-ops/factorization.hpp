#ifndef AAL_SRC_MATH_INT_OPS_FACTORIZATION_HPP
#define AAL_SRC_MATH_INT_OPS_FACTORIZATION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/factorization.hpp */

#include "../../type-traits/integral.hpp"
#include <array>
#include <cassert>
#include <vector>

namespace aal { namespace get_divisor {

template <typename T>
auto all(T n) -> std::vector<T>
{
  static_assert(is_nonbool_integral<T>::value, "argument must be nonbool integer");
  assert(n > 0 && "argument must be positive");

  // divisors are in pairs, let n = a * b, let a be the smaller one, then a <= sqrt(n) <= b, we only need to find all possible a, then calculate b
  std::vector<T> info;
  for (T i = 1; i <= n / i; ++i) {
    if (n % i == 0)
      info.push_back(i);
  }
  for (int idx = info.size() - 1; idx >= 0; --idx) {
    T another = n / info[idx];
    if (another != info[idx])
      info.push_back(another);
  }
  return info;
}

template <typename T>
auto prime(T n) -> std::vector<std::array<T, 2>>
{
  static_assert(is_nonbool_integral<T>::value, "argument must be nonbool integer");
  assert(n > 0 && "argument must be positive");

  // if there exists a prime p of n that is > sqrt(n), then its the only, and its count is exactly 1, otherwise the total product exceeds n
  std::vector<std::array<T, 2>> info;
  for (T i = 2; i <= n / i; ++i) {
    if (n % i == 0)
      info.push_back({i, 0});
    for (; n % i == 0; n /= i) {
      ++info.back()[1];
    }
  }
  if (n > 1)
    info.push_back({n, 1});
  return info;
}

template <typename T>
auto prime(T n, const std::vector<T>& minp) -> std::vector<std::array<T, 2>>
{
  static_assert(is_nonbool_integral<T>::value, "argument must be nonbool integer");
  assert(n > 0 && "argument must be positive");

  // when the smallest prime divisor of every number is known, the time complexity can be reduced to O(logn)
  // because the worst case is n = pow(2, k), where k = log_2 n, any other case costs less computations
  std::vector<std::array<T, 2>> info;
  while (n > 1) {
    int p = minp[n], cnt = 0;
    for (; n % p == 0; n /= p)
      ++cnt;
    info.push_back({p, cnt});
  }
  return info;
}

}} // namespace aal::get_divisor

#endif // AAL_SRC_MATH_INT_OPS_FACTORIZATION_HPP
