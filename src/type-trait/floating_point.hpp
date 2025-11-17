#ifndef AAL_SRC_TYPE_TRAIT_FLOATING_POINT_HPP
#define AAL_SRC_TYPE_TRAIT_FLOATING_POINT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-trait/floating_point.hpp */

#include "../alias/floating_point.hpp"
#include "cvref.hpp"
#include "logical.hpp"

namespace aal {

template <typename T>
struct is_f128 : std::is_same<remove_cv_t<T>, f128>
{
};

// f128 is considered floating-point
template <typename T>
struct is_floating_point : disjunction<std::is_floating_point<T>, is_f128<T>>
{
};

// std::is_floating_point_v<f128> is true in -std=gnu++ mode, which may not always be the desired result
template <typename T>
struct is_standard_floating_point : conjunction<std::is_floating_point<T>, negation<is_f128<T>>>
{
};

namespace detail {

// use specialization to avoid nested conditional_t
template <typename T, typename TFloatingPoint = remove_cv_t<T>>
struct make_higher_precision_selector;

template <typename T>
struct make_higher_precision_selector<T, f32>
{
  using type = claim_cv_t<T, f64>;
};

template <typename T>
struct make_higher_precision_selector<T, f64>
{
  using type = claim_cv_t<T, f80>;
};

template <typename T>
struct make_higher_precision_selector<T, f80>
{
  using type = claim_cv_t<T, f128>;
};

template <typename T>
struct make_higher_precision_selector<T, f128>
{
  using type = T;
};

template <typename T, typename = typename std::enable_if<is_floating_point<T>::value>::type>
struct make_higher_precision_impl
{
  using type = typename detail::make_higher_precision_selector<T>::type;
};

} // namespace detail

// for the given floating-point type, obtains a floating-point that has higher precision,
// if there is no such a type, obtains the given type
// cv-qualifiers are kept
template <typename T>
using make_higher_precision = detail::make_higher_precision_impl<T>;

template <typename T>
using make_higher_precision_t = typename make_higher_precision<T>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_FLOATING_POINT_HPP
