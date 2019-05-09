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

#include <units/dimension.h>

namespace units {

//  inline constexpr base_dimension base_dim_length{"length"};
//  inline constexpr base_dimension base_dim_mass{"mass"};
//  inline constexpr base_dimension base_dim_time{"time"};
//  inline constexpr base_dimension base_dim_current{"current"};
//  inline constexpr base_dimension base_dim_temperature{"temperature"};
//  inline constexpr base_dimension base_dim_substance{"substance"};
//  inline constexpr base_dimension base_dim_luminous_intensity{"luminous intensity"};

  inline constexpr base_dimension base_dim_length{1};
  inline constexpr base_dimension base_dim_mass{2};
  inline constexpr base_dimension base_dim_time{3};
  inline constexpr base_dimension base_dim_current{4};
  inline constexpr base_dimension base_dim_temperature{5};
  inline constexpr base_dimension base_dim_substance{6};
  inline constexpr base_dimension base_dim_luminous_intensity{7};

}  // namespace units
