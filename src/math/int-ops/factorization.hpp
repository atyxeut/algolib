#ifndef AAL_SRC_MATH_INT_OPS_FACTORIZATION_HPP
#define AAL_SRC_MATH_INT_OPS_FACTORIZATION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/factorization.hpp */

#include "../../type-traits/integral.hpp"
#include <array>
#include <cassert>
#include <vector>

namespace aal { namespace get_divisor {

// get all unique divisors of an integer
// std::vector<int> ret = aal::get_divisor::all(36);
// ret is [1, 2, 3, 4, 6, 9, 12, 18, 36]
template <typename T>
auto all(T n) -> std::vector<T>
{
  static_assert(is_nonbool_integral<T>::value, "argument must be integer");
  assert(n > 0 && "argument must be positive");

  // divisors are in pairs, let n = a * b and a <= b, then a <= sqrt(n) <= b, we only need to find all possible a, then calculate b
  std::vector<T> info;
  for (T i = 1; i <= n / i; ++i)
    if (n % i == 0)
      info.push_back(i);

  for (int idx = info.size() - 1; idx >= 0; --idx) {
    T another = n / info[idx];
    if (another != info[idx])
      info.push_back(another);
  }
  return info;
}

// get the prime factorization of an integer n in O(sqrt(n)) time
// int n = 36;
// std::vector<std::array<int, 2>> ret = aal::get_divisor::prime(n);
// ret is [[2, 2], [3, 2]]
template <typename T>
auto prime(T n) -> std::vector<std::array<T, 2>>
{
  static_assert(is_nonbool_integral<T>::value, "argument must be integer");
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

// O(logn) version when the smallest prime divisor of every integer that <= n is known
// because the worst case is n = 2^k, where k = log_2 n, any other case costs less computations
template <typename T>
auto prime(T n, const std::vector<T>& minp) -> std::vector<std::array<T, 2>>
{
  static_assert(is_nonbool_integral<T>::value, "argument must be integer");
  assert(n > 0 && "argument must be positive");

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
