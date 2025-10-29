#ifndef AAL_SRC_TYPE_TRAITS_IO_HPP
#define AAL_SRC_TYPE_TRAITS_IO_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-traits/io.hpp */

#include "cvref.hpp"
#include "sfinae.hpp"
#include <ostream>
#include <utility>

namespace aal {

namespace detail {

template <typename TChar, typename TTraits>
void is_ostream_impl(const std::basic_ostream<TChar, TTraits>&);

} // namespace detail

// check if T is std::basic_ostream<...>
template <typename T, typename = void>
struct is_ostream : std::false_type
{
};

template <typename T>
struct is_ostream<T, void_t<decltype(detail::is_ostream_impl(std::declval<remove_cvref_t<T>>()))>> : std::true_type
{
};

#if CPP14
template <typename T>
constexpr bool is_ostream_v = is_ostream<T>::value;
#endif // C++14

namespace detail {

template <typename T, typename TOstream, typename = void, typename = t_enable_if_t<is_ostream<TOstream>>>
struct is_default_printable_impl : std::false_type
{
};

template <typename T, typename TOstream>
struct is_default_printable_impl<T, TOstream, void_t<decltype(std::declval<remove_cvref_t<TOstream>&>() << std::declval<remove_cvref_t<T>&>())>>
  : std::true_type
{
};

} // namespace detail

// check if T has a dedicated overload for operator <<
// note that templates are not "dedicated", that is to say:
// operator <<(..., int) is, while operator <<(..., TArg&&) is not, even if the latter can actually be used
// a more concrete example:
// std::vector<int> matches the latter, but it's not considered default printable, since there is no operator <<(..., std::vector<int>) overload
template <typename T, typename TOstream>
using is_default_printable = detail::is_default_printable_impl<T, TOstream>;

#if CPP14
template <typename T, typename TOstream>
constexpr bool is_default_printable_v = is_default_printable<T, TOstream>::value;
#endif // C++14

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_IO_HPP
