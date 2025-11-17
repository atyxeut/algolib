#ifndef AAL_SRC_TYPE_TRAIT_CONDITIONAL_HPP
#define AAL_SRC_TYPE_TRAIT_CONDITIONAL_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type-trait/conditional.hpp */

#include <type_traits>

namespace aal {

// backports C++14 std::conditional_t
template <bool B, typename TTrue, typename TFalse>
using conditional_t = typename std::conditional<B, TTrue, TFalse>::type;

template <typename TB, typename TTrue, typename TFalse>
using t_conditional_t = conditional_t<static_cast<bool>(TB::value), TTrue, TFalse>;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAIT_CONDITIONAL_HPP
