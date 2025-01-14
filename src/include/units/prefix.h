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

#include <units/bits/downcasting.h>
#include <units/bits/fixed_string.h>
#include <units/ratio.h>

namespace units {

  namespace detail {

    template<typename PrefixType, Ratio R>
    struct prefix_base : downcast_base<prefix_base<PrefixType, R>> {
      using prefix_type = PrefixType;
      using ratio = R;
    };

  }

  template<typename Child, typename PrefixType, Ratio R, basic_fixed_string Symbol>
  struct prefix : downcast_child<Child, detail::prefix_base<PrefixType, R>> {
    static constexpr auto symbol = Symbol;
  };


  // TODO gcc:92150
  // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92150
  // namespace detail {

  //   template<typename T>
  //   inline constexpr bool is_prefix = false;

  //   template<typename PrefixType, Ratio R, basic_fixed_string Symbol>
  //   inline constexpr bool is_prefix<prefix<PrefixType, R, Symbol>> = true;

  // }  // namespace detail

  template<typename T>
//  concept Prefix = detail::is_prefix<T>;
  concept Prefix = true;

  struct no_prefix;

}  // namespace units
