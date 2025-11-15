#ifndef AAL_SRC_ALIASES_FLOATING_POINT_HPP
#define AAL_SRC_ALIASES_FLOATING_POINT_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/aliases/floating_point.hpp */

// precision (significant digits)
// f32: 6 to 9, f64: 15 to 17, f80: 18 to 20, f128: 33 to 35

using f32 = float;
using f64 = double;
using f80 = long double;

// f128 is provided by compilers, and is not supported by standard type traits
// see https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html for details
// for convenience, we consider that f128 only works on x86 or x86_64
#if !defined(__i386__) && !defined(__x86_64__)
namespace aal { namespace detail {

struct fake_f128;

}} // namespace aal::detail

using f128 = ::aal::detail::fake_f128;
#else
__extension__ using f128 = __float128;
#endif // not x86(_64) architecture

#endif // AAL_SRC_ALIASES_FLOATING_POINT_HPP
