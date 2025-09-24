#ifndef AAL_SRC_TYPE_TRAITS_NEITHER_EITHER_HPP
#define AAL_SRC_TYPE_TRAITS_NEITHER_EITHER_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type_traits/neither_either.hpp */

#include "logical.hpp"

namespace aal {

// checks if neither of the other given types is the same as the first given type
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

// checks if any of the other given types is the same as the first given type
template <typename T, typename... Ts>
struct is_any_of : negation<is_none_of<T, Ts...>>
{
};

#if CPP14
template <typename T, typename... Ts>
constexpr bool is_any_of_v = is_any_of<T, Ts...>::value;
#endif // C++14

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_NEITHER_EITHER_HPP
