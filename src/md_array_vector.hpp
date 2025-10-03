#ifndef AAL_SRC_MD_ARRAY_VECTOR_HPP
#define AAL_SRC_MD_ARRAY_VECTOR_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/md_array_vector.hpp */

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

template <typename T, std::size_t... Dims>
using array = typename details::array_impl<T, Dims...>::type;

template <typename T, std::size_t DimCnt = 1>
using vector = typename details::vector_impl<T, DimCnt>::type;

template <typename TElem, std::size_t Dim, typename T>
AAL_CONSTEXPR20 auto fill_array(std::array<TElem, Dim>& arr, const T& val) -> typename std::enable_if<std::is_convertible<T, TElem>::value>::type
{
  arr.fill(val);
}

template <typename TElem, std::size_t Dim, typename T>
AAL_CONSTEXPR20 auto fill_array(std::array<TElem, Dim>& arr, const T& val) -> typename std::enable_if<!std::is_convertible<T, TElem>::value>::type
{
  for (auto& inner_arr : arr)
    fill_array(inner_arr, val);
}

template <typename TElem, std::size_t... Dims, typename T>
AAL_CONSTEXPR20 auto make_array(const T& val) -> array<TElem, Dims...>
{
  array<TElem, Dims...> arr;
  fill_array(arr, val);
  return arr;
}

template <typename TElem, typename TDim, typename T>
auto make_vector(TDim size, T&& val) -> std::vector<TElem>
{
  static_assert(std::is_integral<TDim>::value && sizeof(TDim) <= sizeof(std::size_t), "wrong type for dim size");
  return std::vector<TElem>(size, std::forward<T>(val));
}

template <typename TElem, typename TDim, typename... Ts>
auto make_vector(TDim size, Ts&&... args) -> vector<TElem, sizeof...(Ts)>
{
  static_assert(std::is_integral<TDim>::value && sizeof(TDim) <= sizeof(std::size_t), "wrong type for dim size");
  return std::vector<vector<TElem, sizeof...(Ts) - 1>>(size, make_vector<TElem>(std::forward<Ts>(args)...));
}

} // namespace aal

#endif // AAL_SRC_MD_ARRAY_VECTOR_HPP
