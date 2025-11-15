#ifndef AAL_SRC_MATH_INT_OPS_BIT_DETAIL_HPP
#define AAL_SRC_MATH_INT_OPS_BIT_DETAIL_HPP

#include "../../../macros/constexpr.hpp"
#include "../../../type-traits/integral.hpp"
#include <limits>

#if AAL_COMPILER_MSVC
#include <intrin.h>
#endif // MSVC compiler

// docs of compiler built-in bit operation:
//   https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html
//   https://learn.microsoft.com/en-us/cpp/intrinsics/bitscanreverse-bitscanreverse64?view=msvc-170

namespace aal { namespace detail { namespace bit {

template <std::size_t Width, typename T>
AAL_CONSTEXPR14 auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u32>::digits, int>::type
{
  constexpr int max_digits = std::numeric_limits<make_unsigned_t<T>>::digits;
#if AAL_COMPILER_MSVC
  unsigned long ret = 0;
  _BitScanReverse(&ret, static_cast<unsigned long>(x));
  return static_cast<int>(max_digits - ret - 1);
#else
  return static_cast<int>(max_digits + __builtin_clz(x) - Width);
#endif // MSVC compiler
}

template <std::size_t Width, typename T>
AAL_CONSTEXPR14 auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u64>::digits, int>::type
{
#if AAL_COMPILER_MSVC
  unsigned long ret = 0;
  _BitScanReverse64(&ret, static_cast<unsigned long long>(x));
  return static_cast<int>(std::numeric_limits<u64>::digits - ret - 1);
#else
  return __builtin_clzll(x);
#endif // MSVC compiler
}

template <std::size_t Width, typename T>
AAL_CONSTEXPR14 auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u128>::digits, int>::type
{
#if AAL_COMPILER_MSVC
  constexpr int u64_width = std::numeric_limits<u128>::digits / 2;
  return x >> u64_width == 0 ? u64_width + countl_zero_impl<u64_width>(static_cast<u64>(x)) : countl_zero_impl<u64_width>(static_cast<u64>(x >> u64_width));
#else
  return __builtin_clzg(static_cast<u128>(x));
#endif // MSVC compiler
}

}}} // namespace aal::detail::bit

#endif // AAL_SRC_MATH_INT_OPS_BIT_DETAIL_HPP
