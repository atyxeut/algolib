#ifndef AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP
#define AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/sieve/linear/divisor_function_list.hpp */

#include <vector>

#include "../../../../macro/warning.hpp"
#include "../../basic-operation/pow.hpp"

namespace aal::sieve::linear {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

// get the sgm list (sgm[i]: value of divisor function sigma_x(i))
// the behavior is undefined if sgm[0] is used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <int x = 1, typename T>
[[nodiscard]] constexpr auto sigma(const std::vector<T>& prime, const std::vector<T>& minp)
{
  constexpr T limit = std::numeric_limits<T>::max();

  std::vector<T> first(minp.size());
  std::vector<T> sgm(minp.size());
  sgm[1] = 1;

  for (T n = minp.size() - 1, i = 2; i <= n; ++i) {
    if (minp[i] == i) {
      assert(!ioverflows::add(1, ipow(i, x), limit) && "the result cannot be represented");
      first[i] = sgm[i] = 1 + ipow(i, x);
    }
    for (T p : prime) {
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      auto composite = static_cast<limit_type>(i) * static_cast<limit_type>(p);
      if (composite > n)
        break;
      auto px = ipow(p, x);
      if (i % p == 0) {
        assert(!ioverflows::mul(px, first[i], limit) && !ioverflows::add(1, px * first[i], limit) && "the result cannot be represented");
        first[composite] = 1 + px * first[i];
        assert(!ioverflows::mul(sgm[i] / first[i], first[composite], limit) && "the result cannot be represented");
        sgm[composite] = sgm[i] / first[i] * first[composite];
        break;
      }
      assert(!ioverflows::add(1, px, limit) && "the result cannot be represented");
      first[composite] = 1 + px;
      assert(!ioverflows::mul(first[composite], sgm[i], limit) && "the result cannot be represented");
      sgm[composite] = first[composite] * sgm[i];
    }
  }
  return sgm;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_INTEGRAL_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP
