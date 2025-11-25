#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP

/* https://github.com/atyxeut/algolib/blob/cpp11/src/math/integral/basic-operation/pow.hpp */

#include <cassert>
#include <limits>

#include "../../../macro/warning.hpp"
#include "../../../type-trait/integral.hpp"
#include "abs.hpp"
#include "overflow_detection.hpp"

namespace aal {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

template <typename T1, typename T2>
auto ipow(T1 a, T2 n) noexcept -> typename std::enable_if<conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, T1>::type
{
  assert(n >= 0 && "exponent must be nonnegative");

  if (n == 0 || a == 1)
    return 1;

  T1 ans = 1;
  while (true) { // don't write for (; n != 0; n >>= 1), since base *= base will be executed an extra time in the end
    if (n & 1) {
#ifndef NDEBUG
      if ((ans < 0) != (a < 0))
        assert(!ioverflows::mul(iabs(ans), iabs(a), iabs(std::numeric_limits<T1>::min())) && "the result cannot be represented");
      else
        assert(!ioverflows::mul(iabs(ans), iabs(a), std::numeric_limits<T1>::max()) && "the result cannot be represented");
#endif
      ans *= a;
    }
    n >>= 1;
    if (n == 0)
      break;
    assert(!ioverflows::mul(iabs(a), iabs(a), std::numeric_limits<T1>::max()) && "the result cannot be represented");
    a *= a;
  }

  return ans;
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP
