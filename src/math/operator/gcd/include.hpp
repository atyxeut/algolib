#ifndef AAL_SRC_MATH_OPERATOR_GCD_INCLUDE_HPP
#define AAL_SRC_MATH_OPERATOR_GCD_INCLUDE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/operator/gcd/include.hpp */

#include "detail.hpp"

namespace aal { namespace op {

// class template representing operator gcd
// auto gcd = aal::op::gcd<int> {};
// int ans = gcd(3, 6);
template <typename T>
using gcd = detail::gcd::gcd_impl<T>;

// class template representing operator lcm
// auto lcm = aal::op::lcm<int> {};
// int ans = lcm(3, 18);
template <typename T>
using lcm = detail::gcd::lcm_impl<T>;

}} // namespace aal::op

#endif // AAL_SRC_MATH_OPERATOR_GCD_INCLUDE_HPP
