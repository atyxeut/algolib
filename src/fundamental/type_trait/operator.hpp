#ifndef AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_OPERATOR_HPP
#define AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_OPERATOR_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/fundamental/type_trait/operator.hpp */

#include <tuple>
#include <type_traits>

namespace aal {

namespace op {

enum class property
{
  associative = 0x00'00'00'01,
  commutative = 0x00'00'00'02
};

constexpr auto operator &(property a, property b) noexcept
{
  return static_cast<property>(static_cast<int>(a) & static_cast<int>(b));
};

constexpr decltype(auto) operator &=(property& a, property b) noexcept
{
  return a = a & b;
};

constexpr auto operator ^(property a, property b) noexcept
{
  return static_cast<property>(static_cast<int>(a) ^ static_cast<int>(b));
};

constexpr decltype(auto) operator ^=(property& a, property b) noexcept
{
  return a = a ^ b;
};

constexpr auto operator |(property a, property b) noexcept
{
  return static_cast<property>(static_cast<int>(a) | static_cast<int>(b));
};

constexpr decltype(auto) operator |=(property& a, property b) noexcept
{
  return a = a | b;
};

} // namespace op

struct unary_operator_tag
{
};

struct binary_operator_tag
{
};

// follow the STL design, provide an empty class for invalid types, make it friendly to tag dispatch
template <typename>
struct operator_traits
{
};

template <typename T> requires requires {
  typename T::operator_category;
  typename T::operand_type;
}
struct operator_traits<T>
{
  using operator_category = T::operator_category;
  using operand_type = T::operand_type;
};

} // namespace aal

#endif // AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_OPERATOR_HPP
