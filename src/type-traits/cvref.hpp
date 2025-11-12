#ifndef AAL_SRC_TYPE_TRAITS_CVREF_HPP
#define AAL_SRC_TYPE_TRAITS_CVREF_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/type-traits/cvref.hpp */

#include <type_traits>

namespace aal {

template <typename T>
struct is_cv : std::bool_constant<std::is_const_v<T> && std::is_volatile_v<T>>
{
};

template <typename T>
constexpr bool is_cv_v = is_cv<T>::value;

namespace detail {

template <typename TFrom, typename TTo, bool = std::is_const_v<TFrom>, bool = std::is_volatile_v<TFrom>>
struct claim_cv_selector;

// branch 1: has both cv qualifiers
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, true, true>
{
  using type = std::add_cv_t<TTo>;
};

// branch 2: has only const qualifier
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, true, false>
{
  using type = std::add_const_t<TTo>;
};

// branch 3: has only volatile qualifier
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, false, true>
{
  using type = std::add_volatile_t<TTo>;
};

// branch 4: has no cv qualifiers
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, false, false>
{
  using type = TTo;
};

} // namespace detail

// extracts the cv-qualifiers of a TFrom and apply them to TTo
template <typename TFrom, typename TTo>
struct claim_cv
{
  using type = detail::claim_cv_selector<TFrom, TTo>::type;
};

template <typename TFrom, typename TTo>
using claim_cv_t = claim_cv<TFrom, TTo>::type;

// shorten std::remove_reference_t
template <typename T>
using remove_ref_t = std::remove_reference_t<T>;

// shorten std::add_lvalue_reference_t
template <typename T>
using add_lref_t = std::add_lvalue_reference_t<T>;

// shorten std::add_rvalue_reference_t
template <typename T>
using add_rref_t = std::add_rvalue_reference_t<T>;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_CVREF_HPP
