#ifndef AAL_SRC_TYPE_TRAIT_IO_HPP
#define AAL_SRC_TYPE_TRAIT_IO_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/type-trait/io.hpp */

#include <ostream>
#include <type_traits>

namespace aal {

// check if T is std::basic_ostream<...>
template <typename T>
struct is_ostream : std::false_type
{
};

template <typename TChar>
struct is_ostream<std::basic_ostream<TChar>> : std::true_type
{
};

template <typename T>
constexpr bool is_ostream_v = is_ostream<T>::value;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_IO_HPP
