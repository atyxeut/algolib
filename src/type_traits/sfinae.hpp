#ifndef AAL_SRC_TYPE_TRAITS_SFINAE_HPP
#define AAL_SRC_TYPE_TRAITS_SFINAE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type_traits/sfinae.hpp */

#include <type_traits>

namespace aal {

template <bool B, typename T = void>
using enable_if_t = typename ::std::enable_if<B, T>::type;

template <typename TB, typename T = void>
using t_enable_if_t = enable_if_t<static_cast<bool>(TB::value), T>;

template <typename...>
using void_t = void;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_SFINAE_HPP
