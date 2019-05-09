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

#include <units/bits/tools.h>
#include <type_traits>

namespace mp {

  namespace detail {

    template<typename T>
    inline constexpr bool is_nontype_list = false;

    template<template<auto...> typename T, auto... NonTypes>
    inline constexpr bool is_nontype_list<T<NonTypes...>> = true;

  }  // namespace detail

  template<typename T>
//  concept bool NonTypeList = detail::is_nontype_list<T>;
  concept bool NonTypeList = true;

  // push_front

  template<NonTypeList List, auto... NonTypes>
  struct nontype_list_push_front;

  template<template<auto...> typename List, auto... OldNonTypes, auto... NewNonTypes>
  struct nontype_list_push_front<List<OldNonTypes...>, NewNonTypes...> {
    using type = List<NewNonTypes..., OldNonTypes...>;
  };

  template<NonTypeList List, auto... NonTypes>
  using nontype_list_push_front_t = nontype_list_push_front<List, NonTypes...>::type;

  // push_back

  template<NonTypeList List, auto... NonTypes>
  struct nontype_list_push_back;

  template<template<auto...> typename List, auto... OldNonTypes, auto... NewNonTypes>
  struct nontype_list_push_back<List<OldNonTypes...>, NewNonTypes...> {
    using type = List<OldNonTypes..., NewNonTypes...>;
  };

  template<NonTypeList List, auto... NonTypes>
  using nontype_list_push_back_t = nontype_list_push_back<List, NonTypes...>::type;

  // split

  namespace detail {

    template<template<auto...> typename List, std::size_t Idx, std::size_t N, auto... NonTypes>
    struct split_impl;

    template<template<auto...> typename List, std::size_t Idx, std::size_t N>
    struct split_impl<List, Idx, N> {
      using first_list = List<>;
      using second_list = List<>;
    };

    template<template<auto...> typename List, std::size_t Idx, std::size_t N, auto T, auto... Rest>
    struct split_impl<List, Idx, N, T, Rest...> : split_impl<List, Idx + 1, N, Rest...> {
      using base = split_impl<List, Idx + 1, N, Rest...>;
      using base_first = base::first_list;
      using base_second = base::second_list;
      using first_list = std::conditional_t<Idx < N, nontype_list_push_front_t<base_first, T>, base_first>;
      using second_list = std::conditional_t<Idx < N, base_second, nontype_list_push_front_t<base_second, T>>;
    };

  }  // namespace detail

  template<NonTypeList List, std::size_t N>
  struct nontype_list_split;

  template<template<auto...> typename List, std::size_t N, auto... NonTypes>
  struct nontype_list_split<List<NonTypes...>, N> {
    static_assert(N <= sizeof...(NonTypes), "Invalid index provided");
    using split = detail::split_impl<List, 0, N, NonTypes...>;
    using first_list = split::first_list;
    using second_list = split::second_list;
  };

  // split_half

  template<NonTypeList List>
  struct nontype_list_split_half;

  template<template<auto...> typename List, auto... NonTypes>
  struct nontype_list_split_half<List<NonTypes...>> : nontype_list_split<List<NonTypes...>, (sizeof...(NonTypes) + 1) / 2> {
  };

  // merge_sorted

  template<NonTypeList SortedList1, NonTypeList SortedList2, typename Pred>
  struct nontype_list_merge_sorted;

  template<NonTypeList SortedList1, NonTypeList SortedList2, typename Pred>
  using nontype_list_merge_sorted_t = nontype_list_merge_sorted<SortedList1, SortedList2, Pred>::type;

  template<template<auto...> typename List, auto... Lhs, typename Pred>
  struct nontype_list_merge_sorted<List<Lhs...>, List<>, Pred> {
    using type = List<Lhs...>;
  };

  template<template<auto...> typename List, auto... Rhs, typename Pred>
  struct nontype_list_merge_sorted<List<>, List<Rhs...>, Pred> {
    using type = List<Rhs...>;
  };

  template<template<auto...> typename List, auto Lhs1, auto... LhsRest, auto Rhs1, auto... RhsRest, typename Pred>
  struct nontype_list_merge_sorted<List<Lhs1, LhsRest...>, List<Rhs1, RhsRest...>, Pred> {
    using type = std::conditional_t<Pred()(Lhs1, Rhs1),
        nontype_list_push_front_t<nontype_list_merge_sorted_t<List<LhsRest...>, List<Rhs1, RhsRest...>, Pred>, Lhs1>,
        nontype_list_push_front_t<nontype_list_merge_sorted_t<List<Lhs1, LhsRest...>, List<RhsRest...>, Pred>, Rhs1>>;
  };

  // sort

  template<NonTypeList List, typename Pred>
  struct nontype_list_sort;

  template<template<auto...> typename List, typename Pred>
  struct nontype_list_sort<List<>, Pred> {
    using type = List<>;
  };

  template<template<auto...> typename List, auto T, typename Pred>
  struct nontype_list_sort<List<T>, Pred> {
    using type = List<T>;
  };

  template<template<auto...> typename List, auto... NonTypes, typename Pred>
  struct nontype_list_sort<List<NonTypes...>, Pred> {
    using types = List<NonTypes...>;
    using split = nontype_list_split_half<List<NonTypes...>>;
    using left = nontype_list_sort<typename split::first_list, Pred>::type;
    using right = nontype_list_sort<typename split::second_list, Pred>::type;
    using type = nontype_list_merge_sorted_t<left, right, Pred>;
  };

  template<NonTypeList List, typename Pred>
  using nontype_list_sort_t = nontype_list_sort<List, Pred>::type;

}  // namespace mp
