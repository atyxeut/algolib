#ifndef AAL_SRC_CONCEPT_IO_HPP
#define AAL_SRC_CONCEPT_IO_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concept/io.hpp */

#include "../type-trait/io.hpp"
#include <utility>

namespace aal {

template <typename TOstream, typename T>
concept ostream_default_interactable = requires(TOstream ostr, T obj) { ostr << obj; };

} // namespace aal

#endif // AAL_SRC_CONCEPT_IO_HPP
