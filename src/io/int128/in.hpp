#ifndef AAL_SRC_IO_INT128_IN_HPP
#define AAL_SRC_IO_INT128_IN_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/io/int128/in.hpp */

#include <istream>
#include <limits>
#include <string>

#include "../../alias/integral.hpp"

template <typename TChar>
auto operator >>(std::basic_istream<TChar>& istr, u128& n)
{
  std::string buffer;
  istr >> buffer;

  n = 0;
  for (auto ch : buffer)
    n = n * 10 + static_cast<u128>(ch - '0');

  return istr;
}

template <typename TChar>
auto operator >>(std::basic_istream<TChar>& istr, i128& n)
{
  std::string buffer;
  istr >> buffer;

  u128 mag = 0;
  int sgn = buffer[0] == '-' ? -1 : 1;
  for (std::size_t i = sgn < 0; i < buffer.size(); ++i)
    mag = mag * 10 + static_cast<u128>(buffer[i] - '0');
  if (mag > std::numeric_limits<i128>::max() || sgn > 0)
    n = static_cast<i128>(mag);
  else
    n = -static_cast<i128>(mag);

  return istr;
}

#endif // AAL_SRC_IO_INT128_IN_HPP
