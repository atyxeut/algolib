#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_BIT_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_BIT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/integral/basic-operation/bit.hpp */

#include <cassert>
#include <limits>

#include "../../../type-trait/integral.hpp"

namespace aal {

namespace detail {

template <std::size_t Width, typename T>
constexpr auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u32>::digits, int>::type
{
  return std::numeric_limits<make_unsigned_t<T>>::digits + __builtin_clz(x) - static_cast<int>(Width);
}

template <std::size_t Width, typename T>
auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u64>::digits, int>::type
{
  return __builtin_clzll(x);
}

template <std::size_t Width, typename T>
auto countl_zero_impl(T x) noexcept -> typename std::enable_if<Width == std::numeric_limits<u128>::digits, int>::type
{
  return __builtin_clzg(static_cast<u128>(x));
}

} // namespace detail

// extended C++20 std::countl_zero, can handle signed and 128-bit integer types
template <typename T>
auto countl_zero(T x) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, int>::type
{
  assert(x >= 0 && "argument must be nonnegative");
  return x == 0 ? std::numeric_limits<make_unsigned_t<T>>::digits : detail::countl_zero_impl<std::numeric_limits<make_unsigned_t<decltype(+x)>>::digits>(x);
}

// extended C++20 std::bit_width, can handle signed and 128-bit integer types
template <typename T>
auto bit_width(T x) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, int>::type
{
  assert(x >= 0 && "argument must be nonnegative");
  return std::numeric_limits<make_unsigned_t<T>>::digits - countl_zero(x);
}

// get the largest integer exponent n such that 2^n <= x
//   similar to GCC's std::__lg, but aal::ilog2(0) is not undefined behavior and returns -1
template <typename T>
auto ilog2(T x) noexcept -> typename std::enable_if<is_nonbool_integral<T>::value, int>::type
{
  assert(x >= 0 && "argument must be nonnegative");
  return bit_width(x) - 1;
}

} // namespace aal

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_BIT_HPP
