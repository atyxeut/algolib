#ifndef AAL_SRC_MISC_MD_ARRAY_VECTOR_INCLUDE_HPP
#define AAL_SRC_MISC_MD_ARRAY_VECTOR_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/misc/md-array-vector/include.hpp */

#include "../../concepts/integral.hpp"
#include "../../type-traits/is_std_array.hpp"
#include "detail.hpp"
#include <utility>

// provide type alias templates and helper function templates to ease the creation of multidimentional std::array and std::vector

namespace aal {

// aal::array<int, 3, 5, 2> arr3d {};
//   same as: std::array<std::array<std::array<int, 2>, 5>, 3> arr3d {};
template <typename T, std::size_t... Dims>
using array = detail::array_impl<T, Dims...>::type;

// aal::vector<int> vec1d;
//   same as: std::vector<int> vec1d;
// aal::vector<int, 4> vec4d;
//   same as: std::vector<std::vector<std::vector<std::vector<int>>>> vec4d;
template <typename T, std::size_t DimCnt = 1>
using vector = detail::vector_impl<T, DimCnt>::type;

// aal::array<int, 3, 5, 2, 10> arr4d;
// int val = -1;
// aal::fill_array(arr4d, val);
//   set every element of a aal::array to val
template <typename TElem, std::size_t Dim, typename T>
constexpr void fill_array(std::array<TElem, Dim>& arr, const T& val)
{
  if constexpr (is_std_array_v<TElem>) {
    for (auto& inner_arr : arr)
      fill_array(inner_arr, val);
  }
  else {
    arr.fill(static_cast<TElem>(val));
  }
}

// auto arr4d = aal::make_array<int, 5, 8, 3, 2>(val);
//   combines aal::array<int, 5, 8, 3, 2> arr4d;
//        and aal::fill_array(arr4d, val);
template <typename TElem, std::size_t... Dims, typename T>
[[nodiscard]] constexpr auto make_array(const T& val)
{
  array<TElem, Dims...> arr;
  fill_array(arr, static_cast<TElem>(val));
  return arr;
}

// auto vec3d = aal::make_vector<int>(x, y, z, 1);
//   same as: auto vec3d = std::vector<std::vector<std::vector<int>>>(
//                           x,
//                           std::vector<std::vector<int>>(y, std::vector<int>(z, 1))
//                         );
// constexpr usage example (error if aal::make_vector is not constexpr):
//   std::cout << [](const std::vector<int>& vec, int sum = 0) consteval
//   {
//     std::ranges::for_each(vec, [&sum](int elem) { return sum += elem; });
//     return sum;
//   }(aal::make_vector<int>(10, -1)) << "\n";
template <typename TElem, standard_integral TDim, typename... Ts> requires (sizeof...(Ts) > 0)
[[nodiscard]] constexpr auto make_vector(TDim first_dim_size, Ts&&... args)
{
  if constexpr (sizeof...(Ts) == 1)
    return std::vector(static_cast<std::size_t>(first_dim_size), static_cast<TElem>(args)...);
  else
    return std::vector(static_cast<std::size_t>(first_dim_size), make_vector<TElem>(std::forward<Ts>(args)...));
}

} // namespace aal

#endif // AAL_SRC_MISC_MD_ARRAY_VECTOR_INCLUDE_HPP
