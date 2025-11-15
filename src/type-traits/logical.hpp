#ifndef AAL_SRC_TYPE_TRAITS_LOGICAL_HPP
#define AAL_SRC_TYPE_TRAITS_LOGICAL_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-traits/logical.hpp */

#include <type_traits>

namespace aal {

// backports C++17 std::negation
template <typename T>
struct negation : std::integral_constant<bool, !static_cast<bool>(T::value)>
{
};

// backports C++17 std::conjunction
template <typename...>
struct conjunction : std::true_type
{
};

template <typename T>
struct conjunction<T> : std::integral_constant<bool, static_cast<bool>(T::value)>
{
};

template <typename T, typename... Ts>
struct conjunction<T, Ts...> : std::conditional<static_cast<bool>(T::value), conjunction<Ts...>, conjunction<T>>::type
{
};

// backports C++17 std::disjunction
template <typename...>
struct disjunction : std::false_type
{
};

template <typename T>
struct disjunction<T> : std::integral_constant<bool, static_cast<bool>(T::value)>
{
};

template <typename T, typename... Ts>
struct disjunction<T, Ts...> : std::conditional<static_cast<bool>(T::value), disjunction<T>, disjunction<Ts...>>::type
{
};

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_LOGICAL_HPP
