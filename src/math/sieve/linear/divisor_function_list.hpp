#ifndef AAL_SRC_MATH_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP
#define AAL_SRC_MATH_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/sieve/linear/divisor_function_list.hpp */

#include "../../int-ops/ipow.hpp"
#include <vector>

// see linear.md for extra information

namespace aal { namespace sieve { namespace linear {

// get the sgm list (sgm[i]: value of divisor function sigma_x(i))
// the behavior is undefined if sgm[0] is used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <int x = 1, typename T>
auto sigma(const std::vector<T>& prime, const std::vector<T>& minp) -> std::vector<T>
{
  T n = minp.size() - 1;

  std::vector<T> first(n + 1);
  std::vector<T> sgm(n + 1);
  sgm[1] = 1;

  for (T i = 2; i <= n; ++i) {
    if (minp[i] == i) {
      assert(!iadd_overflows<T>(1, ipow(i, x)) && "the result cannot be represented");
      first[i] = sgm[i] = 1 + ipow(i, x);
    }
    for (T p : prime) {
      auto composite = static_cast<make_unsigned_t<make_larger_width_t<T>>>(i) * p;
      auto px = ipow(p, x);
      if (composite > n)
        break;
      if (i % p == 0) {
        assert(!imul_overflows<T>(px, first[i]) && "the result cannot be represented");
        assert(!iadd_overflows<T>(1, px * first[i]) && "the result cannot be represented");
        first[composite] = 1 + px * first[i];
        assert(!imul_overflows<T>(sgm[i] / first[i], first[composite]) && "the result cannot be represented");
        sgm[composite] = sgm[i] / first[i] * first[composite];
        break;
      }
      assert(!iadd_overflows<T>(1, px) && "the result cannot be represented");
      first[composite] = 1 + px;
      assert(!imul_overflows<T>(first[composite], sgm[i]) && "the result cannot be represented");
      sgm[composite] = first[composite] * sgm[i];
    }
  }

  return sgm;
}

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP
