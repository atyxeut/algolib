#ifndef AAL_SRC_ALIASES_FLOATING_POINT_HPP
#define AAL_SRC_ALIASES_FLOATING_POINT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/aliases/floating_point.hpp */

#include "../macros/target.hpp"

// provide aliases for floating-point number types

// precision (significant digits)
// f32: 6 to 9, f64: 15 to 17, f80: 18 to 20, f128: 33 to 35

using f32 = float;
using f64 = double;
using f80 = long double;

// f128 is provided by compilers, and is not supported by standard type traits
// there is no f128 for MSVC
// for convenience, we consider that f128 only works on x86 or x86_64
#if AAL_COMPILER_MSVC || !AAL_ARCH_X86 && !AAL_ARCH_X86_64
namespace aal { namespace detail {

struct fake_f128;

}} // namespace aal::detail

using f128 = ::aal::detail::fake_f128;
#else
// details (GCC and Clang): https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html
__extension__ using f128 = __float128;
#endif // MSVC compiler or not x86(_64) architecture

#endif // AAL_SRC_ALIASES_FLOATING_POINT_HPP
