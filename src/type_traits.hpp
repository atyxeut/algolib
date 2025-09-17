#ifndef AAL_SRC_TYPE_TRAITS_HPP
#define AAL_SRC_TYPE_TRAITS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type_traits.hpp */

#include "aliases.hpp"
#include <type_traits>
#include <utility>

namespace aal {

template <bool B>
using bool_constant = ::std::integral_constant<bool, B>;

template <size_t I>
using size_t_constant = ::std::integral_constant<size_t, I>;

template <bool B, typename T = void>
using enable_if_t = typename ::std::enable_if<B, T>::type;

template <typename TB, typename T = void>
using t_enable_if_t = enable_if_t<static_cast<bool>(TB::value), T>;

template <bool B, typename TTrue, typename TFalse>
using conditional_t = typename ::std::conditional<B, TTrue, TFalse>::type;

template <typename TB, typename TTrue, typename TFalse>
using t_conditional_t = conditional_t<static_cast<bool>(TB::value), TTrue, TFalse>;

template <typename T>
struct type_identity
{
  using type = T;
};

template <typename T>
using type_identity_t = typename type_identity<T>::type;

template <typename... Ts>
using common_type_t = typename ::std::common_type<Ts...>::type;

template <typename T>
using remove_cv_t = typename ::std::remove_cv<T>::type;

template <typename T>
using remove_ref_t = typename ::std::remove_reference<T>::type;

template <typename T>
struct remove_cvref
{
  using type = remove_cv_t<remove_ref_t<T>>;
};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

template <typename T>
using add_cv_t = typename ::std::add_cv<T>::type;

template <typename T>
using add_const_t = typename ::std::add_const<T>::type;

template <typename T>
using add_volatile_t = typename ::std::add_volatile<T>::type;

template <typename T>
using add_lref_t = typename ::std::add_lvalue_reference<T>::type;

template <typename T>
using add_rref_t = typename ::std::add_rvalue_reference<T>::type;

template <typename T>
struct negation : bool_constant<!static_cast<bool>(T::value)>
{
};

#if CPP14
template <typename T>
constexpr bool negation_v = negation<T>::value;
#endif // C++14

template <typename...>
struct conjunction : ::std::true_type
{
};

template <typename T>
struct conjunction<T> : bool_constant<static_cast<bool>(T::value)>
{
};

template <typename T, typename... Ts>
struct conjunction<T, Ts...> : t_conditional_t<T, conjunction<Ts...>, conjunction<T>>
{
};

#if CPP14
template <typename... Ts>
constexpr bool conjunction_v = conjunction<Ts...>::value;
#endif // C++14

template <typename...>
struct disjunction : ::std::false_type
{
};

template <typename T>
struct disjunction<T> : bool_constant<static_cast<bool>(T::value)>
{
};

template <typename T, typename... Ts>
struct disjunction<T, Ts...> : t_conditional_t<T, disjunction<T>, disjunction<Ts...>>
{
};

#if CPP14
template <typename... Ts>
constexpr bool disjunction_v = disjunction<Ts...>::value;
#endif // C++14

template <typename T>
struct is_bool : ::std::is_same<remove_cv_t<T>, bool>
{
};

#if CPP14
template <typename T>
constexpr bool is_bool_v = is_bool<T>::value;
#endif // C++14

template <typename T>
struct is_cv : conjunction<::std::is_const<T>, ::std::is_volatile<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_cv_v = is_cv<T>::value;
#endif // C++14

namespace details {

// use specialization to avoid nested conditional_t
template <typename TFrom, typename TTo, bool = ::std::is_const<TFrom>::value, bool = ::std::is_volatile<TFrom>::value>
struct claim_cv_selector;

// branch 1: has both cv qualifiers
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, true, true>
{
  using type = add_cv_t<TTo>;
};

// branch 2: has only const qualifier
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, true, false>
{
  using type = add_const_t<TTo>;
};

// branch 3: has only volatile qualifier
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, false, true>
{
  using type = add_volatile_t<TTo>;
};

// branch 4: has no cv qualifiers
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, false, false>
{
  using type = TTo;
};

} // namespace details

template <typename TFrom, typename TTo>
struct claim_cv
{
  using type = typename details::claim_cv_selector<TFrom, TTo>::type;
};

template <typename TFrom, typename TTo>
using claim_cv_t = typename claim_cv<TFrom, TTo>::type;

template <typename, typename...>
struct is_none_of;

template <typename T, typename T0>
struct is_none_of<T, T0> : negation<::std::is_same<T, T0>>
{
};

template <typename T, typename T0, typename... Ts>
struct is_none_of<T, T0, Ts...> : conjunction<is_none_of<T, T0>, is_none_of<T, Ts...>>
{
};

#if CPP14
template <typename T, typename... Ts>
constexpr bool is_none_of_v = is_none_of<T, Ts...>::value;
#endif // C++14

template <typename T, typename... Ts>
struct is_any_of : negation<is_none_of<T, Ts...>>
{
};

#if CPP14
template <typename T, typename... Ts>
constexpr bool is_any_of_v = is_any_of<T, Ts...>::value;
#endif // C++14

template <typename T>
struct is_int128 : is_any_of<remove_cv_t<T>, i128, u128>
{
};

#if CPP14
template <typename T>
constexpr bool is_int128_v = is_int128<T>::value;
#endif // C++14

template <typename T>
struct is_integral : disjunction<::std::is_integral<T>, is_int128<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_integral_v = is_integral<T>::value;
#endif // C++14

template <typename T>
struct is_standard_integral : conjunction<::std::is_integral<T>, negation<is_int128<T>>>
{
};

#if CPP14
template <typename T>
constexpr bool is_standard_integral_v = is_standard_integral<T>::value;
#endif // C++14

template <typename T>
struct is_nonbool_integral : conjunction<is_integral<T>, negation<is_bool<T>>>
{
};

#if CPP14
template <typename T>
constexpr bool is_nonbool_integral_v = is_nonbool_integral<T>::value;
#endif // C++14

template <typename T>
struct make_signed
{
  // lazy evaluation of std::make_signed<T>::type to avoid compilation error
  using type = typename t_conditional_t<is_int128<T>, claim_cv<T, i128>, ::std::make_signed<T>>::type;
};

template <typename T>
using make_signed_t = typename make_signed<T>::type;

template <typename T>
struct make_unsigned
{
  // lazy evaluation of std::make_unsigned<T>::type to avoid compilation error
  using type = typename t_conditional_t<is_int128<T>, claim_cv<T, u128>, ::std::make_unsigned<T>>::type;
};

template <typename T>
using make_unsigned_t = typename make_unsigned<T>::type;

template <typename T>
struct is_signed : disjunction<::std::is_same<remove_cv_t<T>, i128>, ::std::is_signed<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_signed_v = is_signed<T>::value;
#endif // C++14

template <typename T>
struct is_unsigned : disjunction<::std::is_same<remove_cv_t<T>, u128>, ::std::is_unsigned<T>>
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

template <typename T>
struct is_f128 : ::std::is_same<remove_cv_t<T>, f128>
{
};

#if CPP14
template <typename T>
constexpr bool is_f128_v = is_f128<T>::value;
#endif // C++14

template <typename T>
struct is_floating_point : disjunction<::std::is_floating_point<T>, is_f128<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_floating_point_v = is_floating_point<T>::value;
#endif // C++14

template <typename T>
struct is_standard_floating_point : conjunction<::std::is_floating_point<T>, negation<is_f128<T>>>
{
};

#if CPP14
template <typename T>
constexpr bool is_standard_floating_point_v = is_standard_floating_point<T>::value;
#endif // C++14

namespace details {

// use specialization to avoid nested conditional_t
template <typename T, size_t Width = sizeof(T) < sizeof(i32) ? 0 : sizeof(T)>
struct make_larger_width_selector;

template <typename T>
struct make_larger_width_selector<T, 0>
{
  using type = t_conditional_t<is_signed<T>, claim_cv_t<T, i32>, claim_cv_t<T, u32>>;
};

template <typename T>
struct make_larger_width_selector<T, sizeof(i32)>
{
  using type = t_conditional_t<is_signed<T>, claim_cv_t<T, i64>, claim_cv_t<T, u64>>;
};

template <typename T>
struct make_larger_width_selector<T, sizeof(i64)>
{
  using type = t_conditional_t<is_signed<T>, claim_cv_t<T, i128>, claim_cv_t<T, u128>>;
};

template <typename T>
struct make_larger_width_selector<T, sizeof(i128)>
{
  using type = T;
};

} // namespace details

template <typename T>
struct make_larger_width
{
  static_assert(is_integral<T>::value, "the given type must be integral");
  using type = typename details::make_larger_width_selector<T>::type;
};

template <typename T>
using make_larger_width_t = typename make_larger_width<T>::type;

namespace details {

// use specialization to avoid nested conditional_t
template <typename T, typename TFloatingPoint = remove_cv_t<T>>
struct make_higher_precision_selector;

template <typename T>
struct make_higher_precision_selector<T, f32>
{
  using type = claim_cv_t<T, f64>;
};

template <typename T>
struct make_higher_precision_selector<T, f64>
{
  using type = claim_cv_t<T, f80>;
};

template <typename T>
struct make_higher_precision_selector<T, f80>
{
  using type = claim_cv_t<T, f128>;
};

template <typename T>
struct make_higher_precision_selector<T, f128>
{
  using type = T;
};

} // namespace details

template <typename T>
struct make_higher_precision
{
  static_assert(is_floating_point<T>::value, "the given type must be floating point");
  using type = typename details::make_higher_precision_selector<T>::type;
};

template <typename T>
using make_higher_precision_t = typename make_higher_precision<T>::type;

template <typename T1, typename T2>
struct idiv_result
{
  static_assert(conjunction<is_nonbool_integral<T1>, is_nonbool_integral<T2>>::value, "given two types must be nonbool integral");

  // cv-qualifiers are removed after integral promotion
  using dividend_type = decltype(+::std::declval<T1>()); // the "type1" in the comments
  using divisor_type  = decltype(+::std::declval<T2>()); // the "type2" in the comments

  // branch 1: type2 is unsigned, i.e. the divisor is positive, the result never overflows type1

  // branch 2: type2 is signed, the result type has to be a signed type larger than type1
  //   e.g. -2147483648 (int) / -1 = 2147483648
  //   e.g. 4294967295 (unsigned int) / -1 = -4294967295
  //   both of the above require long long as the result type

  using type = t_conditional_t<is_unsigned<divisor_type>, dividend_type, make_larger_width_t<make_signed_t<dividend_type>>>;

  // if dividend_type is i/u128, then the potential overflow is inevitable when type2 is signed, since there's no larger type
};

template <typename T1, typename T2>
using idiv_result_t = typename idiv_result<T1, T2>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_HPP
