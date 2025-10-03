#ifndef AAL_SRC_ALIASES_INTEGRAL_HPP
#define AAL_SRC_ALIASES_INTEGRAL_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/aliases/integral.hpp */

#include "../macros/compiler_test.hpp"
#include <cstddef>
#include <cstdint>

// clang-format off
using i8  = std::int8_t;
using u8  = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
// clang-format on

using diff_t = std::ptrdiff_t;
using size_t = std::size_t;

// 128-bit integer types are provided by compilers, and are not supported by standard type traits
#if AAL_MSVC
// details (MSVC): https://stackoverflow.com/a/76440171/12192463
#include <__msvc_int128.hpp>
using i128 = std::_Signed128;
using u128 = std::_Unsigned128;
#else
// details (GCC and Clang): https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html
using i128 = __int128;
using u128 = unsigned __int128;
#endif // MSVC

#endif // AAL_SRC_ALIASES_INTEGRAL_HPP
