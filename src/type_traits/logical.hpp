#ifndef AAL_SRC_TYPE_TRAITS_LOGICAL_HPP
#define AAL_SRC_TYPE_TRAITS_LOGICAL_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type_traits/logical.hpp */

#include "../macros/cpp_version_test.hpp"
#include <type_traits>

namespace aal {

template <typename T>
struct negation : ::std::integral_constant<bool, !static_cast<bool>(T::value)>
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
struct conjunction<T> : ::std::integral_constant<bool, static_cast<bool>(T::value)>
{
};

template <typename T, typename... Ts>
struct conjunction<T, Ts...> : ::std::conditional<static_cast<bool>(T::value), conjunction<Ts...>, conjunction<T>>::type
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
struct disjunction<T> : ::std::integral_constant<bool, static_cast<bool>(T::value)>
{
};

template <typename T, typename... Ts>
struct disjunction<T, Ts...> : ::std::conditional<static_cast<bool>(T::value), disjunction<T>, disjunction<Ts...>>::type
{
};

#if CPP14
template <typename... Ts>
constexpr bool disjunction_v = disjunction<Ts...>::value;
#endif // C++14

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_LOGICAL_HPP
