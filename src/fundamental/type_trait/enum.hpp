#ifndef AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_ENUM_HPP
#define AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_ENUM_HPP

#include <type_traits>
#include <utility>

namespace aal {

template <typename>
struct is_enum_flag : std::false_type
{
};

template <typename T>
constexpr bool is_enum_flag_v = is_enum_flag<T>::value;

template <typename T>
concept enum_flag = std::is_scoped_enum_v<T> && is_enum_flag_v<T>;

template <enum_flag T>
[[nodiscard]] constexpr auto operator &(T a, T b) noexcept
{
  return static_cast<T>(std::to_underlying(a) & std::to_underlying(b));
};

template <enum_flag T>
constexpr auto& operator &=(T& a, T b) noexcept
{
  return a = a & b;
};

template <enum_flag T>
[[nodiscard]] constexpr auto operator ^(T a, T b) noexcept
{
  return static_cast<T>(std::to_underlying(a) ^ std::to_underlying(b));
};

template <enum_flag T>
constexpr auto& operator ^=(T& a, T b) noexcept
{
  return a = a ^ b;
};

template <enum_flag T>
[[nodiscard]] constexpr auto operator |(T a, T b) noexcept
{
  return static_cast<T>(std::to_underlying(a) | std::to_underlying(b));
};

template <enum_flag T>
constexpr auto& operator |=(T& a, T b) noexcept
{
  return a = a | b;
};

} // namespace aal

#endif // AAL_SRC_FUNDAMENTAL_TYPE_TRAIT_ENUM_HPP
