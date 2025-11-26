#ifndef AAL_SRC_LIB_IO_INT128_OUT_HPP
#define AAL_SRC_LIB_IO_INT128_OUT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp23/src/lib/io/int128/out.hpp */

// to make the overload of operator << defined in range/out.hpp able to accept ranges that has i128, u128 as elements,
//   this #include order is necessary:
//   #include ".../int128/out.hpp"
//   #include ".../range/out.hpp"

#include <algorithm>
#include <limits>
#include <ostream>
#include <string>

#include "../../../fundamental/alias/integral.hpp"

template <typename TChar>
auto& operator <<(std::basic_ostream<TChar>& ostr, u128 n)
{
  if (n == 0)
    return ostr << 0;

  std::string buffer;
  for (; n; n /= 10)
    buffer += static_cast<char>(n % 10 + '0');
  std::reverse(buffer.begin(), buffer.end());

  return ostr << buffer;
}

template <typename TChar>
auto& operator <<(std::basic_ostream<TChar>& ostr, i128 n)
{
  if (n == std::numeric_limits<i128>::min())
    return ostr << '-' << static_cast<u128>(n);

  if (n < 0)
    return ostr << '-' << static_cast<u128>(-n);

  return ostr << static_cast<u128>(n);
}

#endif // AAL_SRC_LIB_IO_INT128_OUT_HPP
