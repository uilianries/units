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

#include "units/dimension.h"
#include <utility>

using namespace units;

namespace {

  constexpr base_dimension L{1};
  constexpr base_dimension M{2};

  // make_dimension
  constexpr exp e(L, 1);

  static_assert(std::is_same_v<make_dimension_t<exp(L, 1)>, dimension<exp(L, 1)>>);
  static_assert(std::is_same_v<make_dimension_t<exp(L, 1), exp(M, 1)>, dimension<exp(L, 1), exp(M, 1)>>);
  static_assert(std::is_same_v<make_dimension_t<exp(M, 1), exp(L, 1)>, dimension<exp(L, 1), exp(M, 1)>>);
  static_assert(std::is_same_v<make_dimension_t<exp(M, 1), exp(M, 1)>, dimension<exp(M, 2)>>);
  static_assert(std::is_same_v<make_dimension_t<exp(M, 1), exp(M, -1)>, dimension<>>);

  static_assert(std::is_same_v<make_dimension_t<exp(L, 1), exp(M, 1), exp(L, 1), exp(M, 1)>, dimension<exp(L, 2), exp(M, 2)>>);
  static_assert(
      std::is_same_v<make_dimension_t<exp(L, -1), exp(M, -1), exp(L, -1), exp(M, -1)>, dimension<exp(L, -2), exp(M, -2)>>);

  static_assert(std::is_same_v<make_dimension_t<exp(L, 1), exp(M, 1), exp(M, -1)>, dimension<exp(L, 1)>>);
  static_assert(std::is_same_v<make_dimension_t<exp(L, 1), exp(L, -1), exp(M, 1)>, dimension<exp(M, 1)>>);
  static_assert(std::is_same_v<make_dimension_t<exp(L, 1), exp(M, 1), exp(L, -1)>, dimension<exp(M, 1)>>);
  static_assert(std::is_same_v<make_dimension_t<exp(L, 1), exp(M, 1), exp(L, -1), exp(M, -1)>, dimension<>>);

  // dimension_multiply

  static_assert(
      std::is_same_v<dimension_multiply_t<dimension<exp(L, 1)>, dimension<exp(M, 1)>>, dimension<exp(L, 1), exp(M, 1)>>);
  static_assert(std::is_same_v<dimension_multiply_t<dimension<exp(L, 1), exp(M, 1), exp(2, 1)>, dimension<exp(3, 1)>>,
                               dimension<exp(L, 1), exp(M, 1), exp(2, 1), exp(3, 1)>>);
  static_assert(std::is_same_v<dimension_multiply_t<dimension<exp(L, 1), exp(M, 1), exp(2, 1)>, dimension<exp(M, 1)>>,
                               dimension<exp(M, 2), exp(L, 1), exp(2, 1)>>);
  static_assert(std::is_same_v<dimension_multiply_t<dimension<exp(L, 1), exp(M, 1), exp(2, 1)>, dimension<exp(M, -1)>>,
                               dimension<exp(L, 1), exp(2, 1)>>);

  // dimension_divide

  static_assert(
      std::is_same_v<dimension_divide_t<dimension<exp(L, 1)>, dimension<exp(M, 1)>>, dimension<exp(L, 1), exp(M, -1)>>);
  static_assert(std::is_same_v<dimension_divide_t<dimension<exp(L, 1)>, dimension<exp(L, 1)>>, dimension<>>);

}  // namespace
