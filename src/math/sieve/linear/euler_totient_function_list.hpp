#ifndef AAL_SRC_MATH_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP
#define AAL_SRC_MATH_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/sieve/linear/euler_totient_function_list.hpp */

#include "../../../type-traits/integral.hpp"
#include <vector>

// see linear.md for extra information

namespace aal { namespace sieve { namespace linear {

// get the phi list (phi[i]: value of Euler's totient function phi(i))
// the behavior is undefined if phi[0] is used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <typename T>
auto euler_totient(const std::vector<T>& prime, const std::vector<T>& minp) -> std::vector<T>
{
  T n = minp.size() - 1;

  std::vector<T> phi(n + 1);
  phi[1] = 1;

  for (T i = 2; i <= n; ++i) {
    if (minp[i] == i)
      phi[i] = i - 1;
    for (T p : prime) {
      auto composite = static_cast<make_unsigned_t<make_larger_width_t<T>>>(i) * p;
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

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP
