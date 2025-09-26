#ifndef AAL_SRC_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define AAL_SRC_TYPE_TRAITS_TYPE_IDENTITY_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/type_traits/type_identity.hpp */

#include <type_traits>

namespace aal {

template <typename T>
struct type_identity
{
  using type = T;
};

template <typename T>
using type_identity_t = typename type_identity<T>::type;

} // namespace aal

#endif // AAL_SRC_TYPE_TRAITS_TYPE_IDENTITY_HPP
