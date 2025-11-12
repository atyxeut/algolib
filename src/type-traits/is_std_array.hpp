#ifndef AAL_SRC_CONCEPTS_IS_STD_ARRAY_HPP
#define AAL_SRC_CONCEPTS_IS_STD_ARRAY_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-traits/is_std_array.hpp */

#include <array>
#include <type_traits>

namespace aal {

template <typename T>
struct is_std_array : std::false_type
{
};

template <typename T, std::size_t N>
struct is_std_array<std::array<T, N>> : std::true_type
{
};

} // namespace aal

#endif // AAL_SRC_CONCEPTS_IS_STD_ARRAY_HPP
