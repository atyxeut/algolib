#ifndef AAL_SRC_ALIASES_HPP
#define AAL_SRC_ALIASES_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/aliases.hpp */

#include "macros.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>

using i8  = std::int8_t;
using u8  = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;

#if AAL_MSVC
#include <__msvc_int128.hpp>
using i128 = std::_Signed128;
using u128 = std::_Unsigned128;
#else
using i128 = __int128;
using u128 = unsigned __int128;
#endif // MSVC

using diff_t = std::ptrdiff_t;
using size_t = std::size_t;

using f32 = float;
using f64 = double;
using f80 = long double;

#if AAL_MSVC || !AAL_ARCH_X86 && !AAL_ARCH_X86_64
namespace aal { namespace details {

struct fake_f128;

}} // namespace aal::details

using f128 = ::aal::details::fake_f128;
#else
using f128 = __float128;
#endif // MSVC or not x86(_64) architecture

namespace aal {

template <typename T>
using lim = ::std::numeric_limits<T>;

} // namespace aal

#endif // AAL_SRC_ALIASES_HPP
