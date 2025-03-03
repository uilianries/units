// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <units/dimensions/velocity.h>
#include <iostream>

namespace {

using namespace units::literals;

template<units::Length D, units::Time T>
constexpr units::Velocity AUTO avg_speed(D d, T t)
{
  return d / t;
}

template<units::Velocity V, units::Time T>
void example_1(V v, T t)
{
  const units::Length AUTO distance = v * t;
  std::cout << "A car driving " << v << " in a time of " << t << " will pass "
            << units::quantity_cast<units::quantity<units::metre, double>>(distance) << ".\n";
}

void example_2(double distance_v, double duration_v)
{
  units::quantity<units::kilometre> distance(distance_v);
  units::quantity<units::hour> duration(duration_v);
  const auto kmph = quantity_cast<units::kilometre_per_hour>(avg_speed(distance, duration));
  std::cout << "Average speed of a car that makes " << distance << " in "
            << duration << " is " << kmph << ".\n";
}

}

int main()
{
  try {
    example_1(60kmph, 10.0min);
    example_2(220, 2);
  }
  catch (const std::exception& ex) {
    std::cerr << "Unhandled std exception caught: " << ex.what() << '\n';
  }
  catch (...) {
    std::cerr << "Unhandled unknown exception caught\n";
  }
}
