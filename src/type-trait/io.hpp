#ifndef AAL_SRC_TYPE_TRAIT_IO_HPP
#define AAL_SRC_TYPE_TRAIT_IO_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-trait/io.hpp */

#include "cvref.hpp"
#include "sfinae.hpp"
#include <ostream>
#include <utility>

namespace aal {

namespace detail {

template <typename, typename, typename = void>
struct is_ostream_interactable_impl : std::false_type
{
};

template <typename TChar, typename T>
struct is_ostream_interactable_impl<TChar, T, void_t<decltype(std::declval<std::basic_ostream<TChar>&>() << std::declval<T>())>> : std::true_type
{
};

} // namespace detail

// check if T has a operator << overload
// to make aal::is_ostream_interactable<...>::value evaluate to true, the candidate overloads must be already defined above it
template <typename TChar, typename T>
using is_ostream_interactable = detail::is_ostream_interactable_impl<TChar, T>;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_IO_HPP
