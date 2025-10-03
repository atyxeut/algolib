#ifndef AAL_SRC_TYPE_TRAITS_COMMON_TYPE_HPP
#define AAL_SRC_TYPE_TRAITS_COMMON_TYPE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type_traits/common_type.hpp */

#include <type_traits>

namespace aal {

template <typename... Ts>
using common_type_t = typename std::common_type<Ts...>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_COMMON_TYPE_HPP
