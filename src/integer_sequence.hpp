#ifndef AAL_SRC_INTEGER_SEQUENCE_HPP
#define AAL_SRC_INTEGER_SEQUENCE_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/integer_sequence.hpp */

// backports C++14 std::integer_sequence and its helpers, and add custom helpers
// implementation details from https://en.cppreference.com/w/cpp/utility/integer_sequence.html

#include <cstddef>

namespace aal {

template <typename TInt, TInt... Ints>
struct integer_sequence
{
  using value_type = TInt;

  static constexpr std::size_t size() noexcept
  {
    return sizeof...(Ints);
  };
};

template <std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

namespace details {

template <typename TInt, TInt Begin, TInt End, TInt... Ints>
struct make_integer_sequence_impl
{
  using type = typename make_integer_sequence_impl<TInt, Begin + 1, End, Ints..., Begin>::type;
};

template <typename TInt, TInt End, TInt... Ints>
struct make_integer_sequence_impl<TInt, End, End, Ints...>
{
  using type = integer_sequence<TInt, Ints...>;
};

} // namespace details

template <typename TInt, TInt N>
using make_integer_sequence = typename details::make_integer_sequence_impl<TInt, 0, N>::type;

template <std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template <typename... Ts>
using index_sequence_for = make_index_sequence<sizeof...(Ts)>;

} // namespace aal

#endif // AAL_SRC_INTEGER_SEQUENCE_HPP
