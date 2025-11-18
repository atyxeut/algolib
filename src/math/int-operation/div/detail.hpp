#ifndef AAL_SRC_MATH_INT_OPERATION_DIV_DETAIL_HPP
#define AAL_SRC_MATH_INT_OPERATION_DIV_DETAIL_HPP

#include <utility>

#include "../abs.hpp"
#include "../overflow-detection/include.hpp"

namespace aal { namespace idiv { namespace detail {

enum class mode
{
  floor,
  ceil
};

template <typename TDividend, typename TDivisor>
struct final_result
{
  // cv-qualifiers are removed after integral promotion
  using type1 = decltype(+std::declval<TDividend>());
  using type2 = decltype(+std::declval<TDivisor>());

  // branch 1: type2 is unsigned, then the divisor is always positive, so the result never overflows type1

  // branch 2: type2 is signed, the result type has to be a signed type larger than type1
  //   e.g. -2147483648 (int) / -1 = 2147483648 (requires long long)
  //   e.g. 4294967295 (unsigned int) / -1 = -4294967295 (requires long long)

  // obtains a type that guarantees to be able to represent the result, unless there is no such type
  using type = typename std::conditional<is_unsigned<type2>::value, type1, make_larger_width_t<make_signed_t<type1>>>::type;
};

template <typename TDividend, typename TDivisor>
using final_result_t = typename final_result<TDividend, TDividend>::type;

template <mode Mode, typename T1, typename T2>
auto selector(T1 lhs, T2 rhs) noexcept -> final_result_t<T1, T2>
{
  using result_type = final_result_t<T1, T2>;

  // -0 = 0, so no need to consider lhs = 0, rhs < 0 and lhs < 0, rhs = 0 cases
  bool is_ans_negative = (lhs < 0) != (rhs < 0);

  using op_common_type = typename std::common_type<decltype(iabs(lhs)), decltype(iabs(rhs))>::type;
  auto lhs_abs = static_cast<op_common_type>(iabs(lhs));
  auto rhs_abs = static_cast<op_common_type>(iabs(rhs));

  auto q = lhs_abs / rhs_abs;
  bool modify_ans = lhs_abs % rhs_abs != 0;

#ifndef NDEBUG
  if (q > 0) { // no way to overflow if q = 0
    if (!modify_ans) { // r = 0, |ans| = q
      if (is_ans_negative) // ans = -q, so q must be <= result_max + 1
        assert(!ioverflows::add<result_type>(q - 1, 0) && "the result cannot be represented");
      else // ans = q, so q must be <= result_max
        assert(!ioverflows::add<result_type>(q, 0) && "the result cannot be represented");
    }
    else { // r != 0, so |rhs| >= 2, so q is at most floor(unsigned_result_max / 2) = result_max
      if (is_ans_negative) {
        if (Mode == mode::floor) {
          // ans = -q - 1, so q + 1 must be <= result_max + 1, which is always satisfied
        }
        if (Mode == mode::ceil) {
          // ans = -q + 1, so q - 1 must be <= result_max + 1, which is always satisfied
        }
      }
      else {
        if (Mode == mode::floor) {
          // ans = q, so q must be <= result_max, which is always satisfied
        }
        if (Mode == mode::ceil) {
          // ans = q + 1, so q + 1 must be <= result_max
          assert(!ioverflows::add<result_type>(q, 1) && "the ceil div result cannot be represented");
        }
      }
    }
  }
#endif // NDEBUG

  switch (Mode) {
    case mode::floor:
      return is_ans_negative ? -static_cast<result_type>(q + modify_ans) : static_cast<result_type>(q);
    case mode::ceil:
      return is_ans_negative ? -static_cast<result_type>(q) : static_cast<result_type>(q + modify_ans);
  }
}

}}} // namespace aal::idiv::detail

#endif // AAL_SRC_MATH_INT_OPERATION_DIV_DETAIL_HPP
