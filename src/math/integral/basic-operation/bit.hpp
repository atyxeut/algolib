#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_BIT_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_BIT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/math/integral/basic-operation/bit.hpp */

#include <bit>
#include <cassert>
#include <limits>

#include "../../../concept/integral.hpp"

namespace aal {

// extended std::countl_zero, can handle signed and 128-bit integers
template <nonbool_integral T>
[[nodiscard]] constexpr int countl_zero(T x) noexcept
{
  assert(x >= 0 && "argument must be nonnegative");
  if constexpr (standard_integral<T>) {
    return std::countl_zero<make_unsigned_t<T>>(x);
  }
  else {
    constexpr int u64_width = std::numeric_limits<u128>::digits / 2;
    return x >> u64_width == 0 ? u64_width + std::countl_zero<u64>(x) : std::countl_zero<u64>(x >> u64_width);
  }
}

// extended std::bit_width, can handle signed and 128-bit integers
template <nonbool_integral T>
[[nodiscard]] constexpr int bit_width(T x) noexcept
{
  assert(x >= 0 && "argument must be nonnegative");
  return std::numeric_limits<make_unsigned_t<T>>::digits - countl_zero(x);
}

// get the largest integer exponent n such that 2^n <= x
//   similar to GCC's std::__lg, but aal::ilog2(0) is not undefined behavior and returns -1
template <nonbool_integral T>
[[nodiscard]] constexpr int ilog2(T x) noexcept
{
  assert(x >= 0 && "argument must be nonnegative");
  return bit_width(x) - 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_BIT_HPP
