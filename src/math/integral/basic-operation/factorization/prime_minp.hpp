#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/integral/basic-operation/factorization/prime_minp.hpp */

#include <array>
#include <cassert>
#include <vector>

#include "../../../../macro/warning.hpp"
#include "../../../../type-trait/integral.hpp"

namespace aal { namespace get_divisor {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

// O(logn) when the smallest prime divisor of every integer that <= n is known
// because the worst case is n = 2^k, where k = log_2 n, any other case costs less computations
// the behavior is undefined if the second argument is not the actual minp array
template <typename T>
auto prime(T n, const std::vector<T>& minp) -> typename std::enable_if<is_nonbool_integral<T>::value, std::vector<std::array<T, 2>>>::type
{
  assert(0 < n && n < minp.size() && "the first argument is invalid");

  std::vector<std::array<T, 2>> info;
  while (n > 1) {
    T p = minp[n], cnt = 0;
    for (; n % p == 0; n /= p)
      ++cnt;
    info.push_back({p, cnt});
  }
  return info;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

}} // namespace aal::get_divisor

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP
