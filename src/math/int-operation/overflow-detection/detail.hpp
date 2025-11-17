#ifndef AAL_SRC_MATH_INT_OPERATION_OVERFLOW_DETECTION_DETAIL_HPP
#define AAL_SRC_MATH_INT_OPERATION_OVERFLOW_DETECTION_DETAIL_HPP

#include <limits>
#include <type_traits>

namespace aal { namespace ioverflows { namespace detail {

enum class mode
{
  add,
  mul
};

template <typename T>
constexpr bool add_impl(T a, T b, T limit) noexcept
{
  return b > limit || a > limit - b;
}

template <typename T>
constexpr bool mul_impl(T a, T b, T limit) noexcept
{
  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
  return b == 0 ? false : a > limit / b;
}

template <mode Mode, typename TResult, typename T1, typename T2>
constexpr bool selector(T1 a, T2 b) noexcept
{
  using op_common_type = std::common_type_t<T1, T2, TResult>;

  auto a_ = static_cast<op_common_type>(a);
  auto b_ = static_cast<op_common_type>(b);
  auto limit_ = static_cast<op_common_type>(std::numeric_limits<TResult>::max());

  if constexpr (Mode == mode::add)
    return add_impl(a_, b_, limit_);
  else
    return mul_impl(a_, b_, limit_);
}

}}} // namespace aal::ioverflows::detail

#endif // AAL_SRC_MATH_INT_OPERATION_OVERFLOW_DETECTION_DETAIL_HPP
