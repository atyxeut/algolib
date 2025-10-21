#ifndef AAL_SRC_TYPE_TRAITS_INTEGRAL_HPP
#define AAL_SRC_TYPE_TRAITS_INTEGRAL_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-traits/integral.hpp */

#include "../aliases/integral.hpp"
#include "cvref.hpp"
#include "logical.hpp"

namespace aal {

template <typename T>
struct is_bool : std::is_same<remove_cv_t<T>, bool>
{
};

#if CPP14
template <typename T>
constexpr bool is_bool_v = is_bool<T>::value;
#endif // C++14

template <typename T>
struct is_int128 : disjunction<std::is_same<remove_cv_t<T>, i128>, std::is_same<remove_cv_t<T>, u128>>
{
};

#if CPP14
template <typename T>
constexpr bool is_int128_v = is_int128<T>::value;
#endif // C++14

// 128-bit integers are considered integral
template <typename T>
struct is_integral : disjunction<std::is_integral<T>, is_int128<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_integral_v = is_integral<T>::value;
#endif // C++14

// std::is_integral_v<i/u128> is true in -std=gnu++ mode, which may not always be the desired result
template <typename T>
struct is_standard_integral : conjunction<std::is_integral<T>, negation<is_int128<T>>>
{
};

#if CPP14
template <typename T>
constexpr bool is_standard_integral_v = is_standard_integral<T>::value;
#endif // C++14

// 128-bit integers are considered integral
template <typename T>
struct is_nonbool_integral : conjunction<is_integral<T>, negation<is_bool<T>>>
{
};

#if CPP14
template <typename T>
constexpr bool is_nonbool_integral_v = is_nonbool_integral<T>::value;
#endif // C++14

// i128 support is added
template <typename T>
struct is_signed : disjunction<std::is_same<remove_cv_t<T>, i128>, std::is_signed<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_signed_v = is_signed<T>::value;
#endif // C++14

// u128 support is added
template <typename T>
struct is_unsigned : disjunction<std::is_same<remove_cv_t<T>, u128>, std::is_unsigned<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_unsigned_v = is_unsigned<T>::value;
#endif // C++14

template <typename T>
struct is_nonbool_unsigned : conjunction<negation<is_bool<T>>, is_unsigned<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_nonbool_unsigned_v = is_nonbool_unsigned<T>::value;
#endif // C++14

// i128 support is added
template <typename T>
struct make_signed
{
  // lazy evaluation of std::make_signed<T>::type to avoid compilation error
  using type = typename std::conditional<is_int128<T>::value, claim_cv<T, i128>, std::make_signed<T>>::type::type;
};

template <typename T>
using make_signed_t = typename make_signed<T>::type;

// u128 support is added
template <typename T>
struct make_unsigned
{
  // lazy evaluation of std::make_unsigned<T>::type to avoid compilation error
  using type = typename std::conditional<is_int128<T>::value, claim_cv<T, u128>, std::make_unsigned<T>>::type::type;
};

template <typename T>
using make_unsigned_t = typename make_unsigned<T>::type;

namespace details {

// use specialization to avoid nested std::conditional
template <typename T, std::size_t Width = sizeof(T) < sizeof(i32) ? 0 : sizeof(T)>
struct make_larger_width_selector;

template <typename T>
struct make_larger_width_selector<T, 0>
{
  using type = typename std::conditional<is_signed<T>::value, claim_cv_t<T, i32>, claim_cv_t<T, u32>>::type;
};

template <typename T>
struct make_larger_width_selector<T, sizeof(i32)>
{
  using type = typename std::conditional<is_signed<T>::value, claim_cv_t<T, i64>, claim_cv_t<T, u64>>::type;
};

template <typename T>
struct make_larger_width_selector<T, sizeof(i64)>
{
  using type = typename std::conditional<is_signed<T>::value, claim_cv_t<T, i128>, claim_cv_t<T, u128>>::type;
};

template <typename T>
struct make_larger_width_selector<T, sizeof(i128)>
{
  using type = T;
};

} // namespace details

// for the given integer type, obtains i32 if its width is smaller than the width of i32,
// otherwise obtains an integer type with double width, if there is no such a type, obtains the given type
// cv-qualifiers and signedness are kept
template <typename T>
struct make_larger_width
{
  static_assert(is_integral<T>::value, "the given type must be integral");
  using type = typename details::make_larger_width_selector<T>::type;
};

template <typename T>
using make_larger_width_t = typename make_larger_width<T>::type;

struct empty_integral;

namespace details {

template <typename T, typename = typename std::enable_if<disjunction<is_integral<T>, std::is_same<T, empty_integral>>::value>::type>
struct integral_wrapper_impl;

} // namespace details

template <typename T>
using integral_wrapper = details::integral_wrapper_impl<T>;

using empty_integral_wrapper = integral_wrapper<empty_integral>;

template <typename>
struct is_integral_wrapper : std::false_type
{
};

template <typename T>
struct is_integral_wrapper<integral_wrapper<T>> : std::true_type
{
};

#if CPP14
template <typename T>
constexpr bool is_integral_wrapper_v = is_integral_wrapper<T>::value;
#endif // C++14

template <typename T>
struct is_empty_integral_wrapper : std::is_same<T, empty_integral_wrapper>
{
};

#if CPP14
template <typename T>
constexpr bool is_empty_integral_wrapper_v = is_empty_integral_wrapper<T>::value;
#endif // C++14

namespace details {

template <typename>
struct unwrap_integral_impl;

template <>
struct unwrap_integral_impl<empty_integral_wrapper>;

template <typename T>
struct unwrap_integral_impl<integral_wrapper<T>>
{
  using type = T;
};

} // namespace details

template <typename T>
using unwrap_integral = details::unwrap_integral_impl<T>;

template <typename T>
using unwrap_integral_t = typename unwrap_integral<T>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_INTEGRAL_HPP
