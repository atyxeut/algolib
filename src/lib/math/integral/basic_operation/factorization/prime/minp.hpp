#ifndef AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/basic_operation/factorization/prime/minp.hpp */

#include <array>
#include <vector>

#include "../../../../../../fundamental/macro/warning.hpp"
#include "../../../../../../fundamental/type_trait/integral.hpp"

namespace aal::get_divisor::prime {

AAL_INT_WCONVERSION_WCOMPARE_PUSH()

// O(log n) when the smallest prime divisor of every integer that <= n is known
// because the worst case is n = 2^k, where k = log_2 n, any other case costs less computations
// the behavior is undefined if the second argument is not the actual minp array
template <nonbool_integral T>
[[nodiscard]] constexpr auto minp(T n, const std::vector<T>& minp_arr)
{
  assert(0 < n && n < minp_arr.size() && "the first argument is invalid");

  std::vector<std::array<T, 2>> info;
  while (n > 1) {
    T p = minp_arr[n], cnt = 0;
    for (; n % p == 0; n /= p)
      ++cnt;
    info.push_back({p, cnt});
  }
  return info;
}

AAL_INT_WCONVERSION_WCOMPARE_POP()

} // namespace aal::get_divisor::prime

#endif // AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_FACTORIZATION_PRIME_MINP_HPP
