#ifndef AAL_SRC_MATH_INT_OPS_IPOW_HPP
#define AAL_SRC_MATH_INT_OPS_IPOW_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int_ops/ipow.hpp */

#include "overflow_detection.hpp"

namespace aal {

template <typename T1, typename T2>
AAL_CONSTEXPR14 auto ipow(T1 a, T2 n) noexcept -> make_unsigned_t<typename std::common_type<T1, T2>::type>
{
  static_assert(conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, "operands must be nonbool integers");
  assert(a >= 0 && n >= 0 && "operands must be nonnegative");
  assert(a != 0 || n != 0 && "operands can not be both 0");

  if (a == 0)
    return 0;

  using result_type = decltype(ipow(a, n));
  result_type ans = 1;
  result_type base = a;
  while (true) { // don't write for (; n != 0; n >>= 1), base *= base will be executed an extra time in the end
    if (n & 1)
      ans *= base;
    n >>= 1;
    if (n == 0)
      break;
    assert(!imul_overflows<result_type>(base, base) && "the result cannot be represented");
    base *= base;
  }
  return ans;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_IPOW_HPP
