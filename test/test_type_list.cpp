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

namespace {

  using namespace units;
  
  template<auto... NonTypes>
  struct nontype_list;
  
  // nontype_list_push_front

  static_assert(std::is_same_v<nontype_list_push_front_t<nontype_list<>, 1>, nontype_list<1>>);
  static_assert(std::is_same_v<nontype_list_push_front_t<nontype_list<>, 1, 2, 3>, nontype_list<1, 2, 3>>);
  static_assert(std::is_same_v<nontype_list_push_front_t<nontype_list<3>, 1, 2>, nontype_list<1, 2, 3>>);

  // nontype_list_push_back

  static_assert(std::is_same_v<nontype_list_push_back_t<nontype_list<>, 1>, nontype_list<1>>);
  static_assert(std::is_same_v<nontype_list_push_back_t<nontype_list<>, 1, 2, 3>, nontype_list<1, 2, 3>>);
  static_assert(std::is_same_v<nontype_list_push_back_t<nontype_list<3>, 1, 2>, nontype_list<3, 1, 2>>);

  // nontype_list_split

  static_assert(std::is_same_v<nontype_list_split<nontype_list<1>, 0>::first_list, nontype_list<>>);
  static_assert(std::is_same_v<nontype_list_split<nontype_list<1>, 0>::second_list, nontype_list<1>>);

  static_assert(std::is_same_v<nontype_list_split<nontype_list<1>, 1>::first_list, nontype_list<1>>);
  static_assert(std::is_same_v<nontype_list_split<nontype_list<1>, 1>::second_list, nontype_list<>>);

  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2>, 0>::first_list, nontype_list<>>);
  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2>, 0>::second_list, nontype_list<1, 2>>);

  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2>, 1>::first_list, nontype_list<1>>);
  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2>, 1>::second_list, nontype_list<2>>);

  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2>, 2>::first_list, nontype_list<1, 2>>);
  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2>, 2>::second_list, nontype_list<>>);

  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2, 3>, 1>::first_list, nontype_list<1>>);
  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2, 3>, 1>::second_list, nontype_list<2, 3>>);

  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2, 3>, 2>::first_list, nontype_list<1, 2>>);
  static_assert(std::is_same_v<nontype_list_split<nontype_list<1, 2, 3>, 2>::second_list, nontype_list<3>>);

  // nontype_list_split_half

  static_assert(std::is_same_v<nontype_list_split_half<nontype_list<1>>::first_list, nontype_list<1>>);
  static_assert(std::is_same_v<nontype_list_split_half<nontype_list<1>>::second_list, nontype_list<>>);

  static_assert(std::is_same_v<nontype_list_split_half<nontype_list<1, 2>>::first_list, nontype_list<1>>);
  static_assert(std::is_same_v<nontype_list_split_half<nontype_list<1, 2>>::second_list, nontype_list<2>>);

  static_assert(std::is_same_v<nontype_list_split_half<nontype_list<1, 2, 3>>::first_list, nontype_list<1, 2>>);
  static_assert(std::is_same_v<nontype_list_split_half<nontype_list<1, 2, 3>>::second_list, nontype_list<3>>);

  static_assert(
      std::is_same_v<nontype_list_split_half<nontype_list<1, 2, 3, 4>>::first_list, nontype_list<1, 2>>);
  static_assert(
      std::is_same_v<nontype_list_split_half<nontype_list<1, 2, 3, 4>>::second_list, nontype_list<3, 4>>);

  // nontype_list_merge_sorted

  static_assert(std::is_same_v<nontype_list_merge_sorted_t<nontype_list<0>, nontype_list<1>, std::experimental::ranges::less>,
                               nontype_list<0, 1>>);
  static_assert(std::is_same_v<nontype_list_merge_sorted_t<nontype_list<1>, nontype_list<0>, std::experimental::ranges::less>,
                               nontype_list<0, 1>>);

  static_assert(std::is_same_v<nontype_list_merge_sorted_t<nontype_list<27, 38>, nontype_list<3, 43>, std::experimental::ranges::less>,
                               nontype_list<3, 27, 38, 43>>);
  static_assert(
      std::is_same_v<nontype_list_merge_sorted_t<nontype_list<9, 82>, nontype_list<10>, std::experimental::ranges::less>,
                     nontype_list<9, 10, 82>>);

  // nontype_list_sort

  template<NonTypeList List>
  using dim_sort_t = nontype_list_sort_t<List, std::experimental::ranges::less>;

  static_assert(std::is_same_v<dim_sort_t<nontype_list<0>>, nontype_list<0>>);
  static_assert(std::is_same_v<dim_sort_t<nontype_list<0, 1>>, nontype_list<0, 1>>);
  static_assert(std::is_same_v<dim_sort_t<nontype_list<1, 0>>, nontype_list<0, 1>>);
  static_assert(std::is_same_v<dim_sort_t<nontype_list<38, 27, 43, 3, 9, 82, 10>>, nontype_list<3, 9, 10, 27, 38, 43, 82>>);

  // exp_dim_id_less

  template<NonTypeList List>
  using exp_sort_t = nontype_list_sort_t<List, std::experimental::ranges::less>;

  static_assert(std::is_same_v<exp_sort_t<dimension<exp(0, 1)>>, dimension<exp(0, 1)>>);
  static_assert(std::is_same_v<exp_sort_t<dimension<e<0, 1>, e<1, -1>>>, dimension<e<0, 1>, e<1, -1>>>);
  static_assert(std::is_same_v<exp_sort_t<dimension<e<1, 1>, e<0, -1>>>, dimension<e<0, -1>, e<1, 1>>>);

}  // namespace
