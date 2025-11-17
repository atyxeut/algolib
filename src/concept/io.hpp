#ifndef AAL_SRC_CONCEPT_IO_HPP
#define AAL_SRC_CONCEPT_IO_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/concept/io.hpp */

#include "../type-trait/io.hpp"

namespace aal {

// T must have a dedicated overload for operator << to satisfy this concept
// for what is "dedicated", see this example:
// for type int, operator <<(..., int) is, while operator <<(..., TArg&&) is not,
//   even if the latter can actually be selected by overload resolution when the former does not exist
template <typename TOstream, typename T>
concept ostream_default_interactable = requires(TOstream&& ostr, T&& obj) { ostr << obj; };

} // namespace aal

#endif // AAL_SRC_CONCEPT_IO_HPP
