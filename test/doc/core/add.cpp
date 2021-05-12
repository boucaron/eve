#include <eve/function/add.hpp>
#include <eve/function/saturated/add.hpp>
#include <eve/function/promote.hpp>
#include <eve/function/narrow.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 250, 3, 32700}, qi = {4, 1, 1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pi                           = " << pi << '\n'
            << " <- qi                           = " << qi << '\n'
            << " -> add(pi, qi)                  = " << eve::add(pi, qi) << '\n'
            << " -> pi + qi                      = " << pi + qi << '\n'
            << " -> promote(add)(0, pi, qi)      = " << eve::promote(eve::add)(0, pi, qi) << '\n'
            << " -> narrow(add)(char(0), pi, qi) = " << eve::narrow(eve::add)(char(0), pi, qi) << '\n';

  std::int16_t xi = 100, yi = 32700;

  std::cout << "---- scalar" << '\n'
            << " <- xi          = " << xi << '\n'
            << " <- yi          = " << yi << '\n'
            << " -> add(xi, yi) = " << eve::add(xi, yi) << '\n'
            << " -> xi + yi     = " << xi + yi << '\n'; // C++ promotion to int

  std::cout << "---- multi parameters" << '\n'
            << " -> add(pi, pi, pi, 1)                = " << eve::add(pi, pi, pi, 1) << '\n'
            << " -> saturated(eve::add)(pi,12, pi,pi) = " << eve::saturated(eve::add)(pi, 12, pi,pi) << '\n';
  return 0;
}
