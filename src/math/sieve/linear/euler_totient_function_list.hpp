#ifndef AAL_SRC_MATH_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP
#define AAL_SRC_MATH_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/sieve/linear/euler_totient_function_list.hpp */

#include <vector>

#include "../../int-operation/conversion-helper/as_index.hpp"

// see note.md for extra information

namespace aal { namespace sieve { namespace linear {

// get the phi list (phi[i]: value of Euler's totient function phi(i))
// the behavior is undefined if phi[0] is used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <typename T>
auto euler_totient(const std::vector<T>& prime, const std::vector<T>& minp) -> std::vector<T>
{
  std::vector<T> phi(minp.size());
  phi[1] = 1;

  for (T n = static_cast<T>(minp.size() - 1), i = 2; i <= n; ++i) {
    if (minp[as_index(i)] == i)
      phi[as_index(i)] = i - 1;
    for (T p : prime) {
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      auto composite = static_cast<limit_type>(i) * static_cast<limit_type>(p);
      if (composite > static_cast<limit_type>(n))
        break;
      if (i % p == 0) {
        phi[as_index(composite)] = p * phi[as_index(i)];
        break;
      }
      phi[as_index(composite)] = phi[as_index(i)] * (p - 1);
    }
  }

  return phi;
}

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_SIEVE_LINEAR_EULER_TOTIENT_FUNCTION_LIST_HPP
