#pragma once

#include "sorting.hpp"

namespace algo::experimental {
namespace detail {
template <typename Iter, typename ResultIter>
void radix_argsort_impl(Iter begin, Iter end, ResultIter result, int i) {
  auto size = std::distance(begin, end);
  auto bits_count = sizeof(std::iter_value_t<Iter>) * 8;
  if (size < 2 || i >= bits_count) {
    return;
  }
  auto iter_begin = begin;
  auto iter_end = begin + size - 1;
  while (iter_begin != iter_end) {
    auto ith_greatest_bit_begin = ((*iter_begin) >> ((bits_count - 1) - i)) & 1;
    auto ith_greatest_bit_end = ((*iter_end) >> ((bits_count - 1) - i)) & 1;
    if (ith_greatest_bit_begin == 0) {
      ++iter_begin;
    } else if (ith_greatest_bit_end == 1) {
      --iter_end;
    } else {
      std::iter_swap(iter_begin, iter_end);
      auto i = std::distance(begin, iter_begin);
      auto j = std::distance(begin, iter_end);
      std::iter_swap(result + i, result + j);
    }
  }
  auto ith_greatest_bit_begin = ((*iter_begin) >> ((bits_count - 1) - i)) & 1;
  if (ith_greatest_bit_begin == 0) {
    ++iter_begin;
  }
  radix_argsort_impl(begin, iter_begin, result, i + 1);
  radix_argsort_impl(iter_begin, end, result + std::distance(begin, iter_begin),
                     i + 1);
}
} // namespace detail

template <typename Iter, typename ResultIter>
void radix_argsort(Iter begin, Iter end,
                   ResultIter result) requires std::random_access_iterator<Iter>
    &&std::unsigned_integral<std::iter_value_t<Iter>>
        && ::algo::detail::index_iter<ResultIter> {
  std::vector tmp(begin, end);
  std::iota(result, result + std::distance(begin, end), 0);
  detail::radix_argsort_impl(tmp.begin(), tmp.end(), result, 0);
}
} // namespace algo::experimental
