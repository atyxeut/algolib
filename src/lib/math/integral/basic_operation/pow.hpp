#ifndef AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP
#define AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/math/integral/basic_operation/pow.hpp */

#include "../../../../fundamental/macro/warning.hpp"
#include "../../operator/iexp_pow/include.hpp"

namespace aal {

AAL_INT_WCONVERSION_WCOMPARE_PUSH

template <nonbool_integral T1, nonbool_integral T2>
[[nodiscard]] constexpr T1 ipow(T1 a, T2 n) noexcept
{
  assert(n >= 0 && "exponent must be nonnegative");
  return op::iexp_pow<integral_wrapper<T1>, make_unsigned_t<T2>>::operator ()(a, n);
}

AAL_INT_WCONVERSION_WCOMPARE_POP

} // namespace aal

#endif // AAL_SRC_LIB_MATH_INTEGRAL_BASIC_OPERATION_POW_HPP
