#ifndef AAL_SRC_ALIAS_FLOATING_POINT_HPP
#define AAL_SRC_ALIAS_FLOATING_POINT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/alias/floating_point.hpp */

// precision (significant digits)
// f32: 6 to 9, f64: 15 to 17, f80: 18 to 20, f128: 33 to 35

using f32 = float;
using f64 = double;
using f80 = long double;

// f128 is provided by compilers, and is not supported by standard type traits
// there is no f128 for MSVC
// for convenience, we consider that f128 only works on x86 or x86_64
#if defined(_MSC_VER) || (!defined(__i386__) && !defined(__x86_64__))
namespace aal { namespace detail {

struct fake_f128;

}} // namespace aal::detail

using f128 = ::aal::detail::fake_f128;
#else
// see https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html for details (GCC and Clang)
__extension__ using f128 = __float128;
#endif // MSVC compiler or not x86(_64) architecture

#endif // AAL_SRC_ALIAS_FLOATING_POINT_HPP
