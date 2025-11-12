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

template <typename T>
struct is_int128 : disjunction<std::is_same<remove_cv_t<T>, i128>, std::is_same<remove_cv_t<T>, u128>>
{
};

template <typename T>
struct is_integral : disjunction<std::is_integral<T>, is_int128<T>>
{
};

// std::is_integral_v<i/u128> is true in -std=gnu++ mode, which may not always be the desired result
template <typename T>
struct is_standard_integral : conjunction<std::is_integral<T>, negation<is_int128<T>>>
{
};

template <typename T>
struct is_nonbool_integral : conjunction<is_integral<T>, negation<is_bool<T>>>
{
};

template <typename T>
struct is_signed : disjunction<std::is_same<remove_cv_t<T>, i128>, std::is_signed<T>>
{
};

template <typename T>
struct is_unsigned : disjunction<std::is_same<remove_cv_t<T>, u128>, std::is_unsigned<T>>
{
};

template <typename T>
struct is_nonbool_unsigned : conjunction<negation<is_bool<T>>, is_unsigned<T>>
{
};

template <typename T>
struct make_signed
{
  // delay the instantiation of std::make_signed<T> to avoid compilation error
  using type = typename std::conditional<is_int128<T>::value, claim_cv<T, i128>, std::make_signed<T>>::type::type;
};

template <typename T>
using make_signed_t = typename make_signed<T>::type;

template <typename T>
struct make_unsigned
{
  // delay the instantiation of std::make_unsigned<T> to avoid compilation error
  using type = typename std::conditional<is_int128<T>::value, claim_cv<T, u128>, std::make_unsigned<T>>::type::type;
};

template <typename T>
using make_unsigned_t = typename make_unsigned<T>::type;

namespace detail {

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

template <typename T, typename = typename std::enable_if<is_integral<T>::value>::type>
struct make_larger_width_impl
{
  using type = typename detail::make_larger_width_selector<T>::type;
};

} // namespace detail

// for the given integer type, obtains i32 if its width is smaller than the width of i32,
// otherwise obtains an integer type with double width, if there is no such a type, obtains the given type
// cv-qualifiers and signedness are kept
template <typename T>
using make_larger_width = detail::make_larger_width_impl<T>;

template <typename T>
using make_larger_width_t = typename make_larger_width<T>::type;

struct empty_integral;

namespace detail {

template <typename T, typename = typename std::enable_if<disjunction<is_integral<T>, std::is_same<T, empty_integral>>::value>::type>
struct integral_wrapper_impl;

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
struct is_empty_integral_wrapper : std::is_same<T, empty_integral_wrapper>
{
};

template <typename>
struct unwrap_integral;

template <>
struct unwrap_integral<empty_integral_wrapper>;

template <typename T>
struct unwrap_integral<integral_wrapper<T>>
{
  using type = T;
};

template <typename T>
using unwrap_integral_t = typename unwrap_integral<T>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_INTEGRAL_HPP
