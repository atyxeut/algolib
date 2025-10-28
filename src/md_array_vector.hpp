#ifndef AAL_SRC_MD_ARRAY_VECTOR_HPP
#define AAL_SRC_MD_ARRAY_VECTOR_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/md_array_vector.hpp */

// provide type alias templates and helper function templates to ease the creation of multidimentional std::array and std::vector

#include "macros/constexpr.hpp"
#include <array>
#include <cstddef>
#include <utility>
#include <vector>

namespace aal {

namespace details {

template <typename T, std::size_t... Dims>
struct array_impl;

template <typename T, std::size_t Dim>
struct array_impl<T, Dim>
{
  using type = std::array<T, Dim>;
};

template <typename T, std::size_t Dim, std::size_t... Dims>
struct array_impl<T, Dim, Dims...>
{
  using type = std::array<typename array_impl<T, Dims...>::type, Dim>;
};

template <typename T, std::size_t DimCnt>
struct vector_impl
{
  static_assert(DimCnt > 0, "dim count must be positive");
  using type = std::vector<typename vector_impl<T, DimCnt - 1>::type>;
};

template <typename T>
struct vector_impl<T, 1>
{
  using type = std::vector<T>;
};

} // namespace details

// aal::array<int, 3, 5, 2> arr3d {};
// same as: std::array<std::array<std::array<int, 2>, 5>, 3> arr3d {};
template <typename T, std::size_t... Dims>
using array = typename details::array_impl<T, Dims...>::type;

// aal::vector<int> vec1d;
// same as: std::vector<int> vec1d;
// aal::vector<int, 4> vec4d;
// same as: std::vector<std::vector<std::vector<std::vector<int>>>> vec4d;
template <typename T, std::size_t DimCnt = 1>
using vector = typename details::vector_impl<T, DimCnt>::type;

// base case of aal::fill_array
template <typename TElem, std::size_t Dim, typename T>
AAL_CONSTEXPR20 auto fill_array(std::array<TElem, Dim>& arr, const T& val) -> typename std::enable_if<std::is_convertible<T, TElem>::value>::type
{
  arr.fill(val);
}

// set every element of a aal::array to val
// aal::array<int, 3, 5, 2, 10> arr4d;
// int val = -1;
// aal::fill_array(arr4d, val);
template <typename TElem, std::size_t Dim, typename T>
AAL_CONSTEXPR20 auto fill_array(std::array<TElem, Dim>& arr, const T& val) -> typename std::enable_if<!std::is_convertible<T, TElem>::value>::type
{
  for (auto& inner_arr : arr)
    fill_array(inner_arr, val);
}

// auto arr4d = aal::make_array<int, 5, 8, 3, 2>(val);
// combines aal::array<int, 5, 8, 3, 2> arr4d;
//      and aal::fill_array(arr4d, val);
template <typename TElem, std::size_t... Dims, typename T>
AAL_CONSTEXPR20 auto make_array(const T& val) -> array<TElem, Dims...>
{
  array<TElem, Dims...> arr;
  fill_array(arr, val);
  return arr;
}

// base case of aal::make_vector
template <typename TElem, typename TDim, typename T>
auto make_vector(TDim size, T&& val) -> std::vector<TElem>
{
  static_assert(std::is_integral<TDim>::value && sizeof(TDim) <= sizeof(std::size_t), "wrong type for dim size");
  return std::vector<TElem>(size, std::forward<T>(val));
}

// auto vec3d = aal::make_vector<int>(x, y, z, 1);
// same as: auto vec3d = std::vector<std::vector<std::vector<int>>>(
//                         x,
//                         std::vector<std::vector<int>>(y, std::vector<int>(z, 1))
//                      );
template <typename TElem, typename TDim, typename... Ts>
auto make_vector(TDim size, Ts&&... args) -> vector<TElem, sizeof...(Ts)>
{
  static_assert(std::is_integral<TDim>::value && sizeof(TDim) <= sizeof(std::size_t), "wrong type for dim size");
  return std::vector<vector<TElem, sizeof...(Ts) - 1>>(size, make_vector<TElem>(std::forward<Ts>(args)...));
}

} // namespace aal

#endif // AAL_SRC_MD_ARRAY_VECTOR_HPP
