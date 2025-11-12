#ifndef AAL_SRC_TYPE_TRAITS_IO_HPP
#define AAL_SRC_TYPE_TRAITS_IO_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/type-traits/io.hpp */

#include <ostream>
#include <type_traits>
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
struct is_ostream<T, std::void_t<decltype(detail::is_ostream_impl(std::declval<std::remove_cvref_t<T>>()))>> : std::true_type
{
};

template <typename T>
constexpr bool is_ostream_v = is_ostream<T>::value;

// check if T has a dedicated overload for operator <<
// for what is dedicated", see this example:
// operator <<(..., int) is, while operator <<(..., TArg&&) is not, even if the latter can actually be selected by overload resolution
// std::vector<int> matches the latter, but it's not considered default printable, since there is not an overload like operator <<(..., const std::vector<int>&)
template <typename T, typename TOstream, typename = void> requires is_ostream_v<TOstream>
struct is_default_printable : std::false_type
{
};

template <typename T, typename TOstream>
struct is_default_printable<T, TOstream, std::void_t<decltype(std::declval<std::remove_cvref_t<TOstream>&>() << std::declval<std::remove_cvref_t<T>&>())>>
  : std::true_type
{
};

template <typename T, typename TOstream>
constexpr bool is_default_printable_v = is_default_printable<T, TOstream>::value;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_IO_HPP
