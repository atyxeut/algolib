#ifndef AAL_SRC_TYPE_TRAIT_FLOATING_POINT_HPP
#define AAL_SRC_TYPE_TRAIT_FLOATING_POINT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/type-trait/floating_point.hpp */

#include "../alias/floating_point.hpp"
#include "cvref.hpp"

namespace aal {

template <typename T>
struct is_f128 : std::is_same<std::remove_cv_t<T>, f128>
{
};

template <typename T>
constexpr bool is_f128_v = is_f128<T>::value;

// f128 is considered floating-point
template <typename T>
struct is_floating_point : std::disjunction<std::is_floating_point<T>, is_f128<T>>
{
};

template <typename T>
constexpr bool is_floating_point_v = is_floating_point<T>::value;

// std::is_floating_point_v<f128> is true in -std=gnu++ mode, which may not always be the desired result
template <typename T>
struct is_standard_floating_point : std::conjunction<std::is_floating_point<T>, std::negation<is_f128<T>>>
{
};

template <typename T>
constexpr bool is_standard_floating_point_v = is_standard_floating_point<T>::value;

namespace detail {

template <typename T, bool = is_floating_point_v<T>, typename = std::remove_cv_t<T>>
struct make_higher_precision_selector;

template <typename T>
struct make_higher_precision_selector<T, true, f32>
{
  using type = claim_cv_t<T, f64>;
};

template <typename T>
struct make_higher_precision_selector<T, true, f64>
{
  using type = claim_cv_t<T, f80>;
};

template <typename T>
struct make_higher_precision_selector<T, true, f80>
{
  using type = claim_cv_t<T, f128>;
};

template <typename T>
struct make_higher_precision_selector<T, true, f128>
{
  using type = T;
};

} // namespace detail

// for the given floating-point type, obtains a floating-point that has higher precision,
// if there is no such a type, obtains the given type
// cv-qualifiers are kept
template <typename T>
using make_higher_precision = detail::make_higher_precision_selector<T>;

template <typename T>
using make_higher_precision_t = make_higher_precision<T>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_FLOATING_POINT_HPP
