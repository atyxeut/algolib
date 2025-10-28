#ifndef AAL_SRC_DETAIL_MD_ARRAY_VECTOR_HPP
#define AAL_SRC_DETAIL_MD_ARRAY_VECTOR_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/detail/md_array_vector.hpp */

#include <array>
#include <cstddef>
#include <vector>

namespace aal { namespace detail {

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

}} // namespace aal::detail

#endif // AAL_SRC_DETAIL_MD_ARRAY_VECTOR_HPP
