#ifndef AAL_SRC_TYPE_TRAITS_HPP
#define AAL_SRC_TYPE_TRAITS_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type_traits.hpp */

#include "aliases.hpp"
#include <type_traits>

namespace aal {

template <bool B>
using bool_constant = std::integral_constant<bool, B>;

template <size_t I>
using size_t_constant = std::integral_constant<size_t, I>;

template <bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

template <typename TB, typename T = void>
using t_enable_if_t = ::aal::enable_if_t<static_cast<bool>(TB::value), T>;

template <bool B, typename TTrue, typename TFalse>
using conditional_t = typename std::conditional<B, TTrue, TFalse>::type;

template <typename TB, typename TTrue, typename TFalse>
using t_conditional_t = ::aal::conditional_t<static_cast<bool>(TB::value), TTrue, TFalse>;

template <typename T>
struct type_identity
{
  using type = T;
};

template <typename T>
using type_identity_t = typename ::aal::type_identity<T>::type;

template <typename... Ts>
using common_type_t = typename std::common_type<Ts...>::type;

template <typename T>
using remove_cv_t = typename std::remove_cv<T>::type;

template <typename T>
using remove_ref_t = typename std::remove_reference<T>::type;

template <typename T>
struct remove_cvref
{
  using type = ::aal::remove_cv_t<::aal::remove_ref_t<T>>;
};

template <typename T>
using remove_cvref_t = typename ::aal::remove_cvref<T>::type;

template <typename T>
using add_cv_t = typename std::add_cv<T>::type;

template <typename T>
using add_const_t = typename std::add_const<T>::type;

template <typename T>
using add_volatile_t = typename std::add_volatile<T>::type;

template <typename T>
using add_lref_t = typename std::add_lvalue_reference<T>::type;

template <typename T>
using add_rref_t = typename std::add_rvalue_reference<T>::type;

template <typename T>
struct negation : ::aal::bool_constant<!static_cast<bool>(T::value)>
{
};

#if CPP14
template <typename T>
constexpr bool negation_v = ::aal::negation<T>::value;
#endif // C++14

template <typename...>
struct conjunction : std::true_type
{
};

template <typename T>
struct conjunction<T> : ::aal::bool_constant<static_cast<bool>(T::value)>
{
};

template <typename T, typename... Ts>
struct conjunction<T, Ts...> : ::aal::t_conditional_t<T, ::aal::conjunction<Ts...>, ::aal::conjunction<T>>
{
};

#if CPP14
template <typename... Ts>
constexpr bool conjunction_v = ::aal::conjunction<Ts...>::value;
#endif // C++14

template <typename...>
struct disjunction : std::false_type
{
};

template <typename T>
struct disjunction<T> : ::aal::bool_constant<static_cast<bool>(T::value)>
{
};

template <typename T, typename... Ts>
struct disjunction<T, Ts...> : ::aal::t_conditional_t<T, ::aal::disjunction<T>, ::aal::disjunction<Ts...>>
{
};

#if CPP14
template <typename... Ts>
constexpr bool disjunction_v = ::aal::disjunction<Ts...>::value;
#endif // C++14

template <typename T>
struct is_bool : std::is_same<::aal::remove_cv_t<T>, bool>
{
};

#if CPP14
template <typename T>
constexpr bool is_bool_v = ::aal::is_bool<T>::value;
#endif // C++14

template <typename T>
struct is_cv : ::aal::conjunction<std::is_const<T>, std::is_volatile<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_cv_v = ::aal::is_cv<T>::value;
#endif // C++14

namespace details {

// use specialization to avoid nested conditional_t
template <typename TFrom, typename TTo, bool = std::is_const<TFrom>::value, bool = std::is_volatile<TFrom>::value>
struct claim_cv_selector;

// branch 1: has both cv qualifiers
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, true, true>
{
  using type = ::aal::add_cv_t<TTo>;
};

// branch 2: has only const qualifier
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, true, false>
{
  using type = ::aal::add_const_t<TTo>;
};

// branch 3: has only volatile qualifier
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, false, true>
{
  using type = ::aal::add_volatile_t<TTo>;
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
  using type = typename ::aal::details::claim_cv_selector<TFrom, TTo>::type;
};

template <typename TFrom, typename TTo>
using claim_cv_t = typename ::aal::claim_cv<TFrom, TTo>::type;

template <typename, typename...>
struct is_none_of;

template <typename T, typename T0>
struct is_none_of<T, T0> : ::aal::negation<std::is_same<T, T0>>
{
};

template <typename T, typename T0, typename... Ts>
struct is_none_of<T, T0, Ts...> : ::aal::conjunction<::aal::is_none_of<T, T0>, ::aal::is_none_of<T, Ts...>>
{
};

#if CPP14
template <typename T, typename... Ts>
constexpr bool is_none_of_v = ::aal::is_none_of<T, Ts...>::value;
#endif // C++14

template <typename T, typename... Ts>
struct is_any_of : ::aal::negation<::aal::is_none_of<T, Ts...>>
{
};

#if CPP14
template <typename T, typename... Ts>
constexpr bool is_any_of_v = ::aal::is_any_of<T, Ts...>::value;
#endif // C++14

template <typename T>
struct is_int128 : ::aal::is_any_of<::aal::remove_cv_t<T>, i128, u128>
{
};

#if CPP14
template <typename T>
constexpr bool is_int128_v = ::aal::is_int128<T>::value;
#endif // C++14

template <typename T>
struct is_integral : ::aal::disjunction<std::is_integral<T>, ::aal::is_int128<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_integral_v = ::aal::is_integral<T>::value;
#endif // C++14

template <typename T>
struct is_standard_integral : ::aal::conjunction<std::is_integral<T>, ::aal::negation<::aal::is_int128<T>>>
{
};

#if CPP14
template <typename T>
constexpr bool is_standard_integral_v = ::aal::is_standard_integral<T>::value;
#endif // C++14

template <typename T>
struct is_nonbool_integral : ::aal::conjunction<::aal::is_integral<T>, ::aal::negation<::aal::is_bool<T>>>
{
};

#if CPP14
template <typename T>
constexpr bool is_nonbool_integral_v = ::aal::is_nonbool_integral<T>::value;
#endif // C++14

template <typename T>
struct make_signed
{
  // lazy evaluation of std::make_signed<T>::type to avoid compilation error
  using type = typename ::aal::t_conditional_t<::aal::is_int128<T>, ::aal::claim_cv<T, i128>, std::make_signed<T>>::type;
};

template <typename T>
using make_signed_t = typename ::aal::make_signed<T>::type;

template <typename T>
struct make_unsigned
{
  // lazy evaluation of std::make_unsigned<T>::type to avoid compilation error
  using type = typename ::aal::t_conditional_t<::aal::is_int128<T>, ::aal::claim_cv<T, u128>, std::make_unsigned<T>>::type;
};

template <typename T>
using make_unsigned_t = typename ::aal::make_unsigned<T>::type;

template <typename T>
struct is_signed : ::aal::disjunction<std::is_same<::aal::remove_cv_t<T>, i128>, std::is_signed<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_signed_v = ::aal::is_signed<T>::value;
#endif // C++14

template <typename T>
struct is_unsigned : ::aal::disjunction<std::is_same<::aal::remove_cv_t<T>, u128>, std::is_unsigned<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_unsigned_v = ::aal::is_unsigned<T>::value;
#endif // C++14

template <typename T>
struct is_nonbool_unsigned : ::aal::conjunction<::aal::negation<::aal::is_bool<T>>, ::aal::is_unsigned<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_nonbool_unsigned_v = ::aal::is_nonbool_unsigned<T>::value;
#endif // C++14

template <typename T>
struct is_f128 : std::is_same<::aal::remove_cv_t<T>, f128>
{
};

#if CPP14
template <typename T>
constexpr bool is_f128_v = ::aal::is_f128<T>::value;
#endif // C++14

template <typename T>
struct is_floating_point : ::aal::disjunction<std::is_floating_point<T>, ::aal::is_f128<T>>
{
};

#if CPP14
template <typename T>
constexpr bool is_floating_point_v = ::aal::is_floating_point<T>::value;
#endif // C++14

template <typename T>
struct is_standard_floating_point : ::aal::conjunction<std::is_floating_point<T>, ::aal::negation<::aal::is_f128<T>>>
{
};

#if CPP14
template <typename T>
constexpr bool is_standard_floating_point_v = ::aal::is_standard_floating_point<T>::value;
#endif // C++14

namespace details {

// use specialization to avoid nested conditional_t
template <typename T, size_t Width = sizeof(T) < sizeof(i32) ? 0 : sizeof(T)>
struct make_larger_width_selector;

template <typename T>
struct make_larger_width_selector<T, 0>
{
  using type = ::aal::t_conditional_t<::aal::is_signed<T>, ::aal::claim_cv_t<T, i32>, ::aal::claim_cv_t<T, u32>>;
};

template <typename T>
struct make_larger_width_selector<T, sizeof(i32)>
{
  using type = ::aal::t_conditional_t<::aal::is_signed<T>, ::aal::claim_cv_t<T, i64>, ::aal::claim_cv_t<T, u64>>;
};

template <typename T>
struct make_larger_width_selector<T, sizeof(i64)>
{
  using type = ::aal::t_conditional_t<::aal::is_signed<T>, ::aal::claim_cv_t<T, i128>, ::aal::claim_cv_t<T, u128>>;
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
  static_assert(::aal::is_integral<T>::value, "the given type must be integral");
  using type = typename ::aal::details::make_larger_width_selector<T>::type;
};

template <typename T>
using make_larger_width_t = typename ::aal::make_larger_width<T>::type;

namespace details {

// use specialization to avoid nested conditional_t
template <typename T, typename TFloatingPoint = ::aal::remove_cv_t<T>>
struct make_higher_precision_selector;

template <typename T>
struct make_higher_precision_selector<T, f32>
{
  using type = ::aal::claim_cv_t<T, f64>;
};

template <typename T>
struct make_higher_precision_selector<T, f64>
{
  using type = ::aal::claim_cv_t<T, f80>;
};

template <typename T>
struct make_higher_precision_selector<T, f80>
{
  using type = ::aal::claim_cv_t<T, f128>;
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
  static_assert(::aal::is_floating_point<T>::value, "the given type must be floating point");
  using type = typename ::aal::details::make_higher_precision_selector<T>::type;
};

template <typename T>
using make_higher_precision_t = typename ::aal::make_higher_precision<T>::type;

template <typename T1, typename T2>
struct idiv_result
{
  static_assert(
    ::aal::conjunction<::aal::is_nonbool_integral<T1>, ::aal::is_nonbool_integral<T2>>::value, "given two types must be nonbool integral"
  );

  // branch 1: T2 is signed, may require a signed result type whose size > sizeof(T1)
  // e.g. T1 is signed: -2147483648 / -1 = 2147483648LL
  // e.g. T1 is unsigned : 4294967295U / -1 = -4294967295LL

  // branch 2: T2 is unsigned, the result never overflows

  using type = ::aal::t_conditional_t<
    ::aal::is_signed<T2>, ::aal::make_larger_width_t<::aal::make_signed_t<::aal::remove_cv_t<T1>>>, ::aal::remove_cv_t<T1>
  >;
};

template <typename T1, typename T2>
using idiv_result_t = typename ::aal::idiv_result<T1, T2>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_HPP
