#ifndef AAL_SRC_MATH_INT_OPS_DETAIL_OVERFLOW_DETECTION_HPP
#define AAL_SRC_MATH_INT_OPS_DETAIL_OVERFLOW_DETECTION_HPP

#include "../../../macros/constexpr.hpp"
#include <limits>
#include <type_traits>

namespace aal { namespace detail { namespace ioverflow {

enum class mode
{
  add,
  mul
};

template <typename T>
constexpr bool iadd_overflows_impl(T a, T b, T limit)
{
  return b > limit || a > limit - b;
}

template <typename T>
constexpr bool imul_overflows_impl(T a, T b, T limit)
{
  // a * b <= c ==> a <= c / b = floor(c / b) + {c / b} ==> a <= floor(c / b)
  return b == 0 ? false : a > limit / b;
}

template <mode Mode, typename TResult, typename T1, typename T2>
AAL_CONSTEXPR14 bool selector(T1 a, T2 b)
{
  using op_common_type = typename std::common_type<T1, T2, TResult>::type;
  auto a_ = static_cast<op_common_type>(a);
  auto b_ = static_cast<op_common_type>(b);
  auto limit = static_cast<op_common_type>(std::numeric_limits<TResult>::max());

  switch (Mode) {
    case mode::add:
      return iadd_overflows_impl(a_, b_, limit);
    case mode::mul:
      return imul_overflows_impl(a_, b_, limit);
  }
}

}}} // namespace aal::detail::ioverflow

#endif // AAL_SRC_MATH_INT_OPS_DETAIL_OVERFLOW_DETECTION_HPP
