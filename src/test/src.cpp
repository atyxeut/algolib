#include <iostream>
#include <print>

#include "../include/aliases.hpp"
#include "../include/io.hpp"
#include "../include/math.hpp"
#include "../include/misc.hpp"

AAL_INT_WCONVERSION_WCOMPARE_PUSH

int main()
{
  // int128/in.hpp
  i128 a = 1, b = 2;
  u128 c = 3, d = 4;
  u64 e = 5, f = 6;
  // std::cin >> a >> b >> c >> d >> e >> f;

  // int128/out.hpp
  std::cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << "\n";
  std::cout << "----------------------\n";

  // int128/fmt.hpp
  std::println("{}, {}, {}, {}, {}, {}", a, b, c, d, e, f);
  std::cout << "----------------------\n";

  // tuple/out.hpp
  auto t_1 = std::make_tuple(3.14, "asd", 34535, 1ll, 'c');
  std::cout << t_1 << "\n";
  aal::print(std::cerr, t_1, " | ");
  std::cout << "\n----------------------\n";

  auto t_2 = std::make_pair(3.14, "asdf");
  std::cout << t_2 << "\n";
  aal::print(std::cerr, t_2, " ^ ");
  std::cout << "\n----------------------\n";

  // range/out.hpp
  std::vector v {1, 2, 3, 4, 5};
  std::cout << v << "\n";
  aal::print(std::cerr, v, ", ");
  std::cout << "\n----------------------\n";

  auto v1 = aal::make_vector<double>(3, 2, 5, 3, 3.14);
  std::cout << v1 << "\n";
  aal::print(std::cerr, v1, "|");
  std::cout << "\n----------------------\n";

  std::vector<std::tuple<int, std::string, char, double>> t_3 {
    {1, "hello", 'a', 3.14},
    {2, "world", 'b', 4.13}
  };
  std::cout << t_3 << "\n";
  aal::print(std::cerr, t_3, " | ");
  std::cout << "\n----------------------\n";

  auto not_prime = aal::sieve::eratosthenes(10000);
  auto [prime, minp] = aal::sieve::linear::base(10000);
  auto t_4 = aal::sieve::linear::clp(minp);
  auto t_5 = aal::sieve::linear::maxp(prime, minp);
  for (int i = 2; i <= 10; ++i)
    std::cout << t_4[i] << " " << t_5[i] << "\n";
  std::cout << "----------------------\n";

  std::cout << aal::arith_func::big_omega(10000) << "\n";
  std::cout << aal::arith_func::little_omega(10000) << "\n";
  std::cout << aal::get_divisor::prime(10000) << "\n";
  std::cout << aal::get_divisor::prime(10000, minp) << "\n";
  std::cout << "----------------------\n";

  std::cout << aal::arith_func::sigma<0>(50) << "\n";
  std::cout << aal::get_divisor::all(50) << "\n";
  std::cout << "----------------------\n";

  std::cout << aal::arith_func::sigma(50) << "\n";
  std::cout << aal::arith_func::sigma<2>(50) << "\n";
  std::cout << aal::arith_func::sigma<3>(50) << "\n";
  std::cout << aal::arith_func::sigma<4>(50) << "\n";
  auto t_6 = aal::sieve::linear::sigma<2>(prime, minp);
  std::cout << t_6[50] << "\n";
  std::cout << "----------------------\n";

  std::cout << aal::arith_func::euler_totient(10000) << "\n";
  auto t_7 = aal::sieve::linear::euler_totient(prime, minp);
  std::cout << t_7[10000] << "\n";
  std::cout << "----------------------\n";

  // std::cout << aal::gcd(-2'147'483'647 - 1, -2'147'483'647 - 1, -2'147'483'647 - 1, -2'147'483'647 - 1, -2'147'483'647 - 1);
  std::cout << aal::lcm(13553, -1426, 35ull, 46462, 1) << "\n";
  std::cout << "----------------------\n";

  std::cout << aal::idiv::floor(-2'147'483'647 - 1, 1) << "\n";
  std::cout << aal::idiv::ceil(5, 2) << "\n";
  std::cout << aal::ipow(-2, 31) << "\n";
}

AAL_INT_WCONVERSION_WCOMPARE_POP
