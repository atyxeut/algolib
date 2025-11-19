#ifndef AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_HPP
#define AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/math/integral/basic-operation/overflow_detection.hpp */

#include <cassert>
#include <limits>

#include "../../../type-trait/integral.hpp"

namespace aal { namespace overflows {

namespace detail {

enum class imode
{
  add,
  mul
};

template <typename T>
constexpr bool iadd_impl(T a, T b, T limit) noexcept
{
  return b > limit || a > limit - b;
}

template <typename T>
constexpr bool imul_impl(T a, T b, T limit) noexcept
{
  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
  return b == 0 ? false : a > limit / b;
}

template <imode Mode, typename TResult, typename T1, typename T2>
bool iselector(T1 a, T2 b) noexcept
{
  using op_common_type = typename std::common_type<T1, T2, TResult>::type;
  auto a_ = static_cast<op_common_type>(a);
  auto b_ = static_cast<op_common_type>(b);
  auto limit_ = static_cast<op_common_type>(std::numeric_limits<TResult>::max());

  switch (Mode) {
    case imode::add:
      return iadd_impl(a_, b_, limit_);
    case imode::mul:
      return imul_impl(a_, b_, limit_);
  }
}

} // namespace detail

// if a + b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
auto iadd(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<TResult>, is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::iselector<detail::imode::add, TResult>(a, b);
}

// if a * b overflows the given result type, returns true
template <typename TResult, typename T1, typename T2>
auto imul(T1 a, T2 b) noexcept -> typename std::enable_if<conjunction<is_integral<TResult>, is_integral<T1>, is_integral<T2>>::value, bool>::type
{
  assert(a >= 0 && b >= 0 && "arguments must be nonnegative");
  return detail::iselector<detail::imode::mul, TResult>(a, b);
}

}} // namespace aal::overflows

#endif // AAL_SRC_MATH_INTEGRAL_BASIC_OPERATION_OVERFLOW_DETECTION_HPP
