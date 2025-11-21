#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic-operation/factorization/prime_minp.hpp */

#include <array>
#include <cassert>
#include <vector>

#include "../conversion-helper/as_index.hpp"

namespace aal::get_divisor {

// O(logn) when the smallest prime divisor of every integer that <= n is known
// because the worst case is n = 2^k, where k = log_2 n, any other case costs less computations
// the behavior is undefined if the second argument is not the actual minp array
template <nonbool_integral T>
[[nodiscard]] constexpr auto prime(T n, const std::vector<T>& minp)
{
  assert(n > 0 && "the first argument must be positive");
  assert(static_cast<std::size_t>(n) < minp.size() && "the first argument is too large");

  std::vector<std::array<T, 2>> info;
  while (n > 1) {
    T p = minp[as_index(n)], cnt = 0;
    for (; n % p == 0; n /= p)
      ++cnt;
    info.push_back({p, cnt});
  }
  return info;
}

} // namespace aal::get_divisor

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP
