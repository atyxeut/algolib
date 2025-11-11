#ifndef AAL_SRC_MATH_INT_OPS_POW_HPP
#define AAL_SRC_MATH_INT_OPS_POW_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/pow.hpp */

#include "overflow_detection.hpp"

namespace aal {

// compute a^n in O(logn) time, see pow.md for extra information
template <typename T1, typename T2>
AAL_CONSTEXPR14 auto ipow(T1 a, T2 n) noexcept ->
  typename std::enable_if<conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, typename std::common_type<T1, T2>::type>::type
{
  assert(a >= 0 && n >= 0 && "arguments must be nonnegative");
  assert(a != 0 || (n != 0 && "arguments can not be all 0"));

  if (a == 0)
    return 0;

  using result_type = decltype(ipow(a, n));
  result_type ans = 1;
  auto base = static_cast<result_type>(a);

  while (true) { // don't write for (; n != 0; n >>= 1), base *= base will be executed an extra time in the end
    if (n & 1) {
      assert(!imul_overflows<result_type>(ans, base) && "the result cannot be represented");
      ans *= base;
    }
    n >>= 1;
    if (n == 0)
      break;
    assert(!imul_overflows<result_type>(base, base) && "the result cannot be represented");
    base *= base;
  }

  return ans;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_POW_HPP
