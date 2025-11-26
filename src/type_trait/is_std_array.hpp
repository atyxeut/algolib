#ifndef AAL_SRC_TYPE_TRAIT_IS_STD_ARRAY_HPP
#define AAL_SRC_TYPE_TRAIT_IS_STD_ARRAY_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/type_trait/is_std_array.hpp */

#include <array>
#include <type_traits>

namespace aal {

template <typename>
struct is_std_array : std::false_type
{
};

template <typename T, std::size_t N>
struct is_std_array<std::array<T, N>> : std::true_type
{
};

template <typename T>
constexpr bool is_std_array_v = is_std_array<T>::value;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_IS_STD_ARRAY_HPP
