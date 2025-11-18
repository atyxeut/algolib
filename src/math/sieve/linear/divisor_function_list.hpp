#ifndef AAL_SRC_MATH_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP
#define AAL_SRC_MATH_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/sieve/linear/divisor_function_list.hpp */

#include "../../int-operation/conversion-helper/as_index.hpp"
#include "../../int-operation/pow/include.hpp"
#include <vector>

// see note.md for extra information

namespace aal { namespace sieve { namespace linear {

// get the sgm list (sgm[i]: value of divisor function sigma_x(i))
// the behavior is undefined if sgm[0] is used
// the behavior is undefined if the arguments are not the actual prime, minp array
template <int x = 1, typename T>
[[nodiscard]] constexpr auto sigma(const std::vector<T>& prime, const std::vector<T>& minp)
{
  std::vector<T> first(minp.size());
  std::vector<T> sgm(minp.size());
  sgm[1] = 1;

  for (T n = static_cast<T>(minp.size() - 1), i = 2; i <= n; ++i) {
    if (minp[as_index(i)] == i) {
      assert(!ioverflows::add<T>(1, ipow(i, x)) && "the result cannot be represented");
      first[as_index(i)] = sgm[as_index(i)] = 1 + ipow(i, x);
    }
    for (T p : prime) {
      using limit_type = make_unsigned_t<make_larger_width_t<T>>;
      auto composite = static_cast<limit_type>(i) * static_cast<limit_type>(p);
      auto px = ipow(p, x);
      if (composite > static_cast<limit_type>(n))
        break;
      if (i % p == 0) {
        assert(!ioverflows::mul<T>(px, first[as_index(i)]) && "the result cannot be represented");
        assert(!ioverflows::add<T>(1, px * first[as_index(i)]) && "the result cannot be represented");
        first[as_index(composite)] = 1 + px * first[as_index(i)];
        assert(!ioverflows::mul<T>(sgm[as_index(i)] / first[as_index(i)], first[as_index(composite)]) && "the result cannot be represented");
        sgm[as_index(composite)] = sgm[as_index(i)] / first[as_index(i)] * first[as_index(composite)];
        break;
      }
      assert(!ioverflows::add<T>(1, px) && "the result cannot be represented");
      first[as_index(composite)] = 1 + px;
      assert(!ioverflows::mul<T>(first[as_index(composite)], sgm[as_index(i)]) && "the result cannot be represented");
      sgm[as_index(composite)] = first[as_index(composite)] * sgm[as_index(i)];
    }
  }

  return sgm;
}

}}} // namespace aal::sieve::linear

#endif // AAL_SRC_MATH_SIEVE_LINEAR_DIVISOR_FUNCTION_LIST_HPP
