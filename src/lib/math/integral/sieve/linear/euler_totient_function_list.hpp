#ifndef AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/sieve/linear/euler_totient_function_list.hpp */

#include <vector>

#include "../../../../../fundamental/concept/integral.hpp"
#include "../../../../../fundamental/macro/warning.hpp"

namespace aal::sieve::linear {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

// get the phi list (phi[i]: value of Euler's totient function phi(i))
// the behavior is undefined if phi[0] is used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <typename T>
[[nodiscard]] constexpr auto euler_totient(const std::vector<T>& prime, const std::vector<T>& minp)
{
  std::vector<T> phi(minp.size());
  phi[1] = 1;

  for (T n = minp.size() - 1, i = 2; i <= n; ++i) {
    if (minp[i] == i)
      phi[i] = i - 1;
    for (T p : prime) {
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      auto composite = static_cast<limit_type>(i) * p;
      if (composite > n)
        break;
      if (i % p == 0) {
        phi[composite] = p * phi[i];
        break;
      }
      phi[composite] = phi[i] * (p - 1);
    }
  }
  return phi;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace aal::sieve::linear

#endif // AAL_SRC_LIB_MATH_INTEGRAL_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP
