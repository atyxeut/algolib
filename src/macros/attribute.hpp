#ifndef AAL_SRC_MACROS_ATTRIBUTE_HPP
#define AAL_SRC_MACROS_ATTRIBUTE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros/attribute.hpp */

#include "cpp_version.hpp"

// see https://en.cppreference.com/w/cpp/language/attributes.html for details

#if AAL_CPP17
#define AAL_ATTRIBUTE_FALLTHROUGH [[fallthrough]]
#define AAL_ATTRIBUTE_NODISCARD   [[nodiscard]]
#else
#define AAL_ATTRIBUTE_FALLTHROUGH
#define AAL_ATTRIBUTE_NODISCARD
#endif

#endif // AAL_SRC_MACROS_ATTRIBUTE_HPP
