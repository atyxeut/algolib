#ifndef AAL_SRC_TYPE_TRAITS_RANGE_HPP
#define AAL_SRC_TYPE_TRAITS_RANGE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-traits/range.hpp */

#include "cvref.hpp"
#include "sfinae.hpp"
#include <iterator>
#include <utility>

namespace aal {

template <typename T, typename = void>
struct can_call_std_begin : std::false_type
{
};

template <typename T>
struct can_call_std_begin<T, void_t<decltype(std::begin(std::declval<remove_cvref_t<T>&>()))>> : std::true_type
{
};

#if AAL_CPP14
template <typename T>
constexpr bool can_call_std_begin_v = can_call_std_begin<T>::value;
#endif // C++14

template <typename T, typename = void>
struct can_call_std_end : std::false_type
{
};

template <typename T>
struct can_call_std_end<T, void_t<decltype(std::end(std::declval<remove_cvref_t<T>&>()))>> : std::true_type
{
};

#if AAL_CPP14
template <typename T>
constexpr bool can_call_std_end_v = can_call_std_end<T>::value;
#endif // C++14

template <typename T>
struct is_range : std::integral_constant<bool, can_call_std_begin<T>::value && can_call_std_end<T>::value>
{
};

#if AAL_CPP14
template <typename T>
constexpr bool is_range_v = is_range<T>::value;
#endif // C++14

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_RANGE_HPP
