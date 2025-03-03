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

#pragma once

#include <units/bits/hacks.h>

namespace units {

#if __GNUC__ < 10

  template<typename T>
  concept Number = std::regular<T> &&
      std::totally_ordered<T> &&
      requires(T a, T b) {
        { a + b } -> T;
        { a - b } -> T;
        { a * b } -> T;
        { a / b } -> T;
        { +a } -> T;
        { -a } -> T;
        { a += b } -> T&;
        { a -= b } -> T&;
        { a *= b } -> T&;
        { a /= b } -> T&;
        { T{0} };    // can construct a T from a zero
        // …
  };

#else

  template<typename T>
  concept Number = std::regular<T> &&
      std::totally_ordered<T> &&
      requires(T a, T b) {
        { a + b } -> std::same_as<T>;
        { a - b } -> std::same_as<T>;
        { a * b } -> std::same_as<T>;
        { a / b } -> std::same_as<T>;
        { +a } -> std::same_as<T>;
        { -a } -> std::same_as<T>;
        { a += b } -> std::same_as<T&>;
        { a -= b } -> std::same_as<T&>;
        { a *= b } -> std::same_as<T&>;
        { a /= b } -> std::same_as<T&>;
        { T{0} };    // can construct a T from a zero
        // …
  };

#endif

  // InstanceOf

}  // namespace units
