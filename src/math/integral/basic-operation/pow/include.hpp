#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_INCLUDE_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/math/integral/basic-operation/pow/include.hpp */

#include "../overflow_detection.hpp"

namespace aal {

// compute a^n in O(logn) time
template <nonbool_integral T1, nonbool_integral T2>
[[nodiscard]] constexpr auto ipow(T1 a, T2 n) noexcept
{
  assert(a >= 0 && n >= 0 && "arguments must be nonnegative");
  assert(a != 0 || (n != 0 && "arguments can not be both 0"));

  if (a == 0)
    return 0;

  using result_type = std::common_type_t<T1, T2>;

  result_type ans = 1;
  auto base = static_cast<result_type>(a);

  while (true) { // don't write for (; n != 0; n >>= 1), since base *= base will be executed an extra time in the end
    if (n & 1) {
      assert(!overflows::imul<result_type>(ans, base) && "the result cannot be represented");
      ans *= base;
    }
    n >>= 1;
    if (n == 0)
      break;
    assert(!overflows::imul<result_type>(base, base) && "the result cannot be represented");
    base *= base;
  }

  return ans;
}

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_POW_INCLUDE_HPP
