#ifndef AAL_SRC_TYPE_TRAITS_CONDITIONAL_HPP
#define AAL_SRC_TYPE_TRAITS_CONDITIONAL_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type_traits/conditional.hpp */

#include <type_traits>

namespace aal {

template <bool B, typename TTrue, typename TFalse>
using conditional_t = typename ::std::conditional<B, TTrue, TFalse>::type;

// same as conditional_t, except that the first template parameter is a type parameter
// the given type must have a member constant value that is convertible to bool
template <typename TB, typename TTrue, typename TFalse>
using t_conditional_t = conditional_t<static_cast<bool>(TB::value), TTrue, TFalse>;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_CONDITIONAL_HPP
