#ifndef AAL_SRC_FUNDAMENTAL_ALIAS_INTEGRAL_HPP
#define AAL_SRC_FUNDAMENTAL_ALIAS_INTEGRAL_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

// clang-format off

using i8  = std::int8_t;
using u8  = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;

// 128-bit integers are compiler extensions, and are not supported by standard type traits
#ifdef _MSC_VER
  #if _MSC_VER >= 1934
    // details: https://stackoverflow.com/a/76440171/12192463
    #include <__msvc_int128.hpp>
    using i128 = std::_Signed128;
    using u128 = std::_Unsigned128;
  #else
    using i128 = void;
    using u128 = void;
  #endif // msvc version >= 19.34
#else // gcc or clang
  // details: https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html
  __extension__ using i128 = __int128;
  __extension__ using u128 = unsigned __int128;
#endif // msvc

// clang-format on

using imx = std::conditional_t<std::is_same_v<i128, void>, i64, i128>;
using umx = std::conditional_t<std::is_same_v<u128, void>, u64, u128>;

using isize = std::ptrdiff_t;
using usize = std::size_t;

#endif // AAL_SRC_FUNDAMENTAL_ALIAS_INTEGRAL_HPP
