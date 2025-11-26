#ifndef AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_INTEGRAL_HPP
#define AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_INTEGRAL_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/fundamental/type_trait/integral.hpp */

#include <cassert>
#include <concepts>
#include <limits>

#include "../alias/integral.hpp"
#include "cvref.hpp"

namespace aal {

struct integral_tag
{
};

template <typename T>
concept integral_tagged = requires {
  { T::type_category } -> std::same_as<integral_tag>;
};

template <typename T>
struct is_bool : std::is_same<std::remove_cv_t<T>, bool>
{
};

template <typename T>
constexpr bool is_bool_v = is_bool<T>::value;

template <typename T>
struct is_i128 : std::bool_constant<!std::is_void_v<T> && std::is_same_v<std::remove_cv_t<T>, i128>>
{
};

template <typename T>
constexpr bool is_i128_v = is_i128<T>::value;

template <typename T>
struct is_u128 : std::bool_constant<!std::is_void_v<T> && std::is_same_v<std::remove_cv_t<T>, u128>>
{
};

template <typename T>
constexpr bool is_u128_v = is_u128<T>::value;

template <typename T>
struct is_int128 : std::bool_constant<is_i128_v<T> || is_u128_v<T>>
{
};

template <typename T>
constexpr bool is_int128_v = is_int128<T>::value;

template <typename T>
struct is_integral : std::bool_constant<std::is_integral_v<T> || is_int128_v<T> || integral_tagged<T>>
{
};

template <typename T>
constexpr bool is_integral_v = is_integral<T>::value;

template <typename T>
concept integral = is_integral_v<T>;

// std::is_integral_v<i/u128> is true in -std=gnu++ mode, which may not always be the desired result
template <typename T>
struct is_standard_integral : std::bool_constant<std::is_integral_v<T> && !is_int128_v<T>>
{
};

template <typename T>
constexpr bool is_standard_integral_v = is_standard_integral<T>::value;

template <typename T>
concept standard_integral = is_standard_integral_v<T>;

template <typename T>
struct is_nonbool_integral : std::bool_constant<integral<T> && !is_bool_v<T>>
{
};

template <typename T>
constexpr bool is_nonbool_integral_v = is_nonbool_integral<T>::value;

template <typename T>
concept nonbool_integral = is_nonbool_integral_v<T>;

template <typename T>
struct is_signed : std::bool_constant<is_i128_v<T> || std::is_signed_v<T>>
{
};

template <typename T>
constexpr bool is_signed_v = is_signed<T>::value;

template <typename T>
concept signed_integral = is_signed_v<T>;

template <typename T>
struct is_unsigned : std::bool_constant<is_u128_v<T> || std::is_unsigned_v<T>>
{
};

template <typename T>
constexpr bool is_unsigned_v = is_unsigned<T>::value;

template <typename T>
concept unsigned_integral = is_unsigned_v<T>;

template <typename T>
struct is_nonbool_unsigned : std::bool_constant<nonbool_integral<T> && unsigned_integral<T>>
{
};

template <typename T>
constexpr bool is_nonbool_unsigned_v = is_nonbool_unsigned<T>::value;

template <typename T>
concept nonbool_unsigned = is_nonbool_unsigned_v<T>;

template <typename T>
struct make_signed
{
  // delay the instantiation of std::make_signed<T> to avoid error
  using type = std::conditional_t<is_int128_v<T>, claim_cv<T, i128>, std::make_signed<T>>::type;
};

template <typename T>
using make_signed_t = make_signed<T>::type;

template <typename T>
struct make_unsigned
{
  // delay the instantiation of std::make_unsigned<T> to avoid error
  using type = std::conditional_t<is_int128_v<T>, claim_cv<T, u128>, std::make_unsigned<T>>::type;
};

template <typename T>
using make_unsigned_t = make_unsigned<T>::type;

namespace detail {

template <typename T, bool = is_integral_v<T>, std::size_t = sizeof(T) < sizeof(i32) ? 0 : sizeof(T)>
struct make_larger_width_selector;

template <typename T>
struct make_larger_width_selector<T, true, 0>
{
  using type = std::conditional_t<is_signed_v<T>, claim_cv_t<T, i32>, claim_cv_t<T, u32>>;
};

template <typename T>
struct make_larger_width_selector<T, true, sizeof(i32)>
{
  using type = std::conditional_t<is_signed_v<T>, claim_cv_t<T, i64>, claim_cv_t<T, u64>>;
};

template <typename T>
struct make_larger_width_selector<T, true, sizeof(i64)>
{
  using type = std::conditional_t<is_signed_v<T>, claim_cv_t<T, imax>, claim_cv_t<T, umax>>;
};

template <typename T>
struct make_larger_width_selector<T, true, sizeof(i128)>
{
  using type = T;
};

} // namespace detail

// for the given integer type, obtains i32 if its width is smaller than the width of i32,
// otherwise obtains an integer type with double width, if there is no such a type, obtains the given type
// cv-qualifiers and signedness are kept
template <typename T>
using make_larger_width = detail::make_larger_width_selector<T>;

template <typename T>
using make_larger_width_t = make_larger_width<T>::type;

namespace ioverflows {

[[nodiscard]] constexpr bool add(umax a, umax b, umax limit) noexcept
{
  return b > limit || a > limit - b;
}

[[nodiscard]] constexpr bool mul(umax a, umax b, umax limit) noexcept
{
  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
  return b == 0 ? false : a > limit / b;
}

} // namespace ioverflows

// an improved version of std::abs, can handle unsigned integer types and i/u128, and never overflows
//   no compilation error: unsigned int _ = aal::iabs(1u);
//   no overflow: unsigned int _ = aal::iabs(-2147483647 - 1);
template <typename T> requires is_nonbool_integral_v<T>
[[nodiscard]] constexpr auto iabs(T n) noexcept
{
  using result_type = make_unsigned_t<T>;
  // for negative n, ~n + 1 is |n| if the bit representation is two's complement
  return n >= 0 ? static_cast<result_type>(n) : ~static_cast<result_type>(n) + 1;
};

template <typename>
struct integral_wrapper;

template <typename T> requires is_nonbool_integral_v<T>
struct integral_wrapper<T>
{
  T val;

  integral_wrapper() = default;

  // enable implicit conversion from T
  constexpr integral_wrapper(T other) noexcept : val {other} {}

  // enable implicit conversion to T
  constexpr operator T() const noexcept
  {
    return val;
  }

  constexpr integral_wrapper& operator +=(integral_wrapper other) noexcept
  {
#ifndef NDEBUG
    if ((val < 0) == (other.val < 0))
      assert(
        !ioverflows::add(iabs(val), iabs(other.val), iabs(val < 0 ? std::numeric_limits<T>::min() : std::numeric_limits<T>::max())) && "addition overflows"
      );
#endif
    val += other.val;
    return *this;
  }

  [[nodiscard]] friend constexpr auto operator +(integral_wrapper a, integral_wrapper b) noexcept
  {
    return a += b;
  }

  constexpr integral_wrapper& operator *=(integral_wrapper other) noexcept
  {
#ifndef NDEBUG
    assert(
      !ioverflows::mul(iabs(val), iabs(other.val), iabs((val < 0) != (other.val < 0) ? std::numeric_limits<T>::min() : std::numeric_limits<T>::max()))
      && "multiplication overflows"
    );
#endif
    val *= other.val;
    return *this;
  }

  [[nodiscard]] friend constexpr auto operator *(integral_wrapper a, integral_wrapper b) noexcept
  {
    return a *= b;
  }
};

// clang-format off

using i8_t   = integral_wrapper<i8>;
using u8_t   = integral_wrapper<u8>;
using i16_t  = integral_wrapper<i16>;
using u16_t  = integral_wrapper<u16>;
using i32_t  = integral_wrapper<i32>;
using u32_t  = integral_wrapper<u32>;
using i64_t  = integral_wrapper<i64>;
using u64_t  = integral_wrapper<u64>;
using i128_t = integral_wrapper<i128>;
using u128_t = integral_wrapper<u128>;
using imax_t = integral_wrapper<imax>;
using umax_t = integral_wrapper<umax>;

// clang-format on

using isize_t = integral_wrapper<isize>;
using usize_t = integral_wrapper<usize>;

} // namespace aal

#endif // AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_INTEGRAL_HPP
