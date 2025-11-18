#ifndef AAL_SRC_TYPE_TRAIT_IO_HPP
#define AAL_SRC_TYPE_TRAIT_IO_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/type-trait/io.hpp */

#include <ostream>
#include <type_traits>
#include <utility>

namespace aal {

namespace detail {

template <typename, typename, typename = void>
struct is_ostream_interactable_impl : std::false_type
{
};

template <typename TChar, typename T>
struct is_ostream_interactable_impl<TChar, T, std::void_t<decltype(std::declval<std::basic_ostream<TChar>&>() << std::declval<T>())>> : std::true_type
{
};

} // namespace detail

// check if T has a operator << overload
// to make aal::is_ostream_interactable<...>::value evaluate to true, the candidate overloads must be already defined above it
template <typename TChar, typename T>
using is_ostream_interactable = detail::is_ostream_interactable_impl<TChar, T>;

template <typename TChar, typename T>
constexpr bool is_ostream_interactable_v = is_ostream_interactable<TChar, T>::value;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_IO_HPP
