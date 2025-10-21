#ifndef AAL_SRC_MATH_INT_OPS_BIT_HPP
#define AAL_SRC_MATH_INT_OPS_BIT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/int-ops/bit.hpp */

#include "../../macros/constexpr.hpp"
#include "../../macros/target.hpp"
#include "../../type-traits/integral.hpp"
#include <cassert>
#include <cstddef>
#include <limits>

// compiler built-in bit operation docs:
// https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html
// https://learn.microsoft.com/en-us/cpp/intrinsics/bitscanreverse-bitscanreverse64?view=msvc-170

#if AAL_MSVC
#include <intrin.h>
#endif // MSVC

namespace aal {

namespace details {

template <std::size_t Width, typename T>
AAL_CONSTEXPR14 auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u32>::digits, int>::type
{
  constexpr int max_digits = std::numeric_limits<make_unsigned_t<T>>::digits;
#if AAL_MSVC
  unsigned long ret;
  _BitScanReverse(&ret, x);
  return max_digits - ret - 1;
#else
  return max_digits + __builtin_clz(x) - Width;
#endif // MSVC
}

template <std::size_t Width, typename T>
AAL_CONSTEXPR14 auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u64>::digits, int>::type
{
#if AAL_MSVC
  unsigned long ret;
  _BitScanReverse64(&ret, x);
  return std::numeric_limits<u64>::digits - ret - 1;
#else
  return __builtin_clzll(x);
#endif // MSVC
}

template <std::size_t Width, typename T>
AAL_CONSTEXPR14 auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u128>::digits, int>::type
{
#if AAL_MSVC
  constexpr int u64_width = std::numeric_limits<u128>::digits / 2;
  return x >> u64_width == 0 ? u64_width + countl_zero_impl<u64_width>(static_cast<u64>(x)) : countl_zero_impl<u64_width>(static_cast<u64>(x >> u64_width));
#else
  return __builtin_clzg(static_cast<u128>(x));
#endif // MSVC
}

} // namespace details

template <typename T>
AAL_CONSTEXPR14 int countl_zero(T x) noexcept
{
  static_assert(is_nonbool_integral<T>::value, "operand must be nonbool integer");
  assert(x >= 0 && "the given operand must be nonnegative");
  return x == 0 ? std::numeric_limits<make_unsigned_t<T>>::digits : details::countl_zero_impl<std::numeric_limits<make_unsigned_t<decltype(+x)>>::digits>(x);
}

template <typename T>
AAL_CONSTEXPR14 int bit_width(T x) noexcept
{
  static_assert(is_nonbool_integral<T>::value, "operand must be nonbool integer");
  assert(x >= 0 && "the given operand must be nonnegative");
  return std::numeric_limits<make_unsigned_t<T>>::digits - countl_zero(x);
}

template <typename T>
AAL_CONSTEXPR14 int ilog2(T x) noexcept
{
  static_assert(is_nonbool_integral<T>::value, "operand must be nonbool integer");
  assert(x >= 0 && "the given operand must be nonnegative");
  return bit_width(x) - 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INT_OPS_BIT_HPP
