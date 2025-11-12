#ifndef AAL_SRC_IO_INT128_FMT_HPP
#define AAL_SRC_IO_INT128_FMT_HPP

/* https://github.com/atyxeut/algolib/blob/cpp20/src/io/int128/fmt.hpp */

#include "../../aliases/integral.hpp"
#include <algorithm>
#include <format>
#include <limits>
#include <string>

template <>
struct std::formatter<u128>
{
  constexpr auto parse(auto& parse_ctx)
  {
    return parse_ctx.begin();
  }

  auto format(u128 n, auto& fmt_ctx) const
  {
    std::string buffer;
    if (n == 0) {
      buffer += '0';
    }
    else {
      for (; n; n /= 10)
        buffer += static_cast<char>(n % 10 + '0');
      std::reverse(buffer.begin(), buffer.end());
    }

    return std::format_to(fmt_ctx.out(), "{}", buffer);
  }
};

template <>
struct std::formatter<i128>
{
  constexpr auto parse(auto& parse_ctx)
  {
    return parse_ctx.begin();
  }

  auto format(i128 n, auto& fmt_ctx) const
  {
    if (n == std::numeric_limits<i128>::min())
      return std::format_to(fmt_ctx.out(), "-{}", static_cast<u128>(n));

    if (n < 0)
      return std::format_to(fmt_ctx.out(), "-{}", static_cast<u128>(-n));

    return std::format_to(fmt_ctx.out(), "{}", static_cast<u128>(n));
  }
};

#endif // AAL_SRC_IO_INT128_FMT_HPP
