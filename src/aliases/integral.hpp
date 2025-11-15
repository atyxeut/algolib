#ifndef AAL_SRC_ALIASES_INTEGRAL_HPP
#define AAL_SRC_ALIASES_INTEGRAL_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/aliases/integral.hpp */

#include <cstddef>
#include <cstdint>

using i8 = std::int8_t;
using u8 = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;

using usize = std::size_t;
using ssize = std::ptrdiff_t;

// 128-bit integers are provided by compilers, and are not supported by standard type traits
// see https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html for details
__extension__ using i128 = __int128;
__extension__ using u128 = unsigned __int128;

#endif // AAL_SRC_ALIASES_INTEGRAL_HPP
