#ifndef AAL_SRC_TYPE_TRAIT_INTEGRAL_HPP
#define AAL_SRC_TYPE_TRAIT_INTEGRAL_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/type-trait/integral.hpp */

#include "../alias/integral.hpp"
#include "cvref.hpp"

namespace aal {

template <typename T>
struct is_bool : std::is_same<std::remove_cv_t<T>, bool>
{
};

template <typename T>
constexpr bool is_bool_v = is_bool<T>::value;

template <typename T>
struct is_int128 : std::disjunction<std::is_same<std::remove_cv_t<T>, i128>, std::is_same<std::remove_cv_t<T>, u128>>
{
};

template <typename T>
constexpr bool is_int128_v = is_int128<T>::value;

template <typename T>
struct is_integral : std::disjunction<std::is_integral<T>, is_int128<T>>
{
};

template <typename T>
constexpr bool is_integral_v = is_integral<T>::value;

// std::is_integral_v<i/u128> is true in -std=gnu++ mode, which may not always be the desired result
template <typename T>
struct is_standard_integral : std::conjunction<std::is_integral<T>, std::negation<is_int128<T>>>
{
};

template <typename T>
constexpr bool is_standard_integral_v = is_standard_integral<T>::value;

template <typename T>
struct is_nonbool_integral : std::conjunction<is_integral<T>, std::negation<is_bool<T>>>
{
};

template <typename T>
constexpr bool is_nonbool_integral_v = is_nonbool_integral<T>::value;

template <typename T>
struct is_signed : std::disjunction<std::is_same<std::remove_cv_t<T>, i128>, std::is_signed<T>>
{
};

template <typename T>
constexpr bool is_signed_v = is_signed<T>::value;

template <typename T>
struct is_unsigned : std::disjunction<std::is_same<std::remove_cv_t<T>, u128>, std::is_unsigned<T>>
{
};

template <typename T>
constexpr bool is_unsigned_v = is_unsigned<T>::value;

template <typename T>
struct is_nonbool_unsigned : std::conjunction<std::negation<is_bool<T>>, is_unsigned<T>>
{
};

template <typename T>
constexpr bool is_nonbool_unsigned_v = is_nonbool_unsigned<T>::value;

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

template <typename T, bool = is_integral_v<T>, std::size_t Width = sizeof(T) < sizeof(i32) ? 0 : sizeof(T)>
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
  using type = std::conditional_t<is_signed_v<T>, claim_cv_t<T, i128>, claim_cv_t<T, u128>>;
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

struct empty_integral;

namespace detail {

template <typename T, bool = std::disjunction_v<is_integral<T>, std::is_same<T, empty_integral>>>
struct integral_wrapper_impl;

template <typename T>
struct integral_wrapper_impl<T, true>
{
  using type = T;
};

} // namespace detail

template <typename T>
using integral_wrapper = detail::integral_wrapper_impl<T>;

using empty_integral_wrapper = integral_wrapper<empty_integral>;

template <typename>
struct is_integral_wrapper : std::false_type
{
};

template <typename T>
struct is_integral_wrapper<integral_wrapper<T>> : std::true_type
{
};

template <typename T>
constexpr bool is_integral_wrapper_v = is_integral_wrapper<T>::value;

template <typename T>
struct is_empty_integral_wrapper : std::is_same<T, empty_integral_wrapper>
{
};

template <typename T>
constexpr bool is_empty_integral_wrapper_v = is_empty_integral_wrapper<T>::value;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_INTEGRAL_HPP
