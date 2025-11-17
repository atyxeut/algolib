#ifndef AAL_SRC_TYPE_TRAIT_CVREF_HPP
#define AAL_SRC_TYPE_TRAIT_CVREF_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-trait/cvref.hpp */

#include <type_traits>

namespace aal {

template <typename T>
struct is_cv : std::integral_constant<bool, std::is_const<T>::value && std::is_volatile<T>::value>
{
};

// backports C++14 std::remove_cv_t
template <typename T>
using remove_cv_t = typename std::remove_cv<T>::type;

namespace detail {

template <typename TFrom, typename TTo, bool = std::is_const<TFrom>::value, bool = std::is_volatile<TFrom>::value>
struct claim_cv_selector;

// branch 1: has both cv qualifiers
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, true, true>
{
  using type = typename std::add_cv<TTo>::type;
};

// branch 2: has only const qualifier
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, true, false>
{
  using type = typename std::add_const<TTo>::type;
};

// branch 3: has only volatile qualifier
template <typename TFrom, typename TTo>
struct claim_cv_selector<TFrom, TTo, false, true>
{
  using type = typename std::add_volatile<TTo>::type;
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
  using type = typename detail::claim_cv_selector<TFrom, TTo>::type;
};

template <typename TFrom, typename TTo>
using claim_cv_t = typename claim_cv<TFrom, TTo>::type;

// backports C++14 std::remove_reference_t
template <typename T>
using remove_ref_t = typename std::remove_reference<T>::type;

// backports C++20 std::remove_cvref
template <typename T>
struct remove_cvref
{
  using type = remove_cv_t<remove_ref_t<T>>;
};

// backports C++20 std::remove_cvref_t
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

// backports C++14 std::add_lvalue_reference_t
template <typename T>
using add_lref_t = typename std::add_lvalue_reference<T>::type;

// backports C++14 std::add_rvalue_reference_t
template <typename T>
using add_rref_t = typename std::add_rvalue_reference<T>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_CVREF_HPP
