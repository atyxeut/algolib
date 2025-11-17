#ifndef AAL_SRC_TYPE_TRAIT_NEITHER_EITHER_HPP
#define AAL_SRC_TYPE_TRAIT_NEITHER_EITHER_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/type-trait/neither_either.hpp */

#include <type_traits>

namespace aal {

// checks if neither of the other given types is the same as the first given type
template <typename, typename...>
struct is_none_of;

template <typename T, typename T0>
struct is_none_of<T, T0> : std::negation<std::is_same<T, T0>>
{
};

template <typename T, typename T0, typename... Ts>
struct is_none_of<T, T0, Ts...> : std::conjunction<is_none_of<T, T0>, is_none_of<T, Ts...>>
{
};

template <typename T, typename... Ts>
constexpr bool is_none_of_v = is_none_of<T, Ts...>::value;

// checks if any of the other given types is the same as the first given type
template <typename T, typename... Ts>
struct is_any_of : std::negation<is_none_of<T, Ts...>>
{
};

template <typename T, typename... Ts>
constexpr bool is_any_of_v = is_any_of<T, Ts...>::value;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_NEITHER_EITHER_HPP
