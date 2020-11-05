#pragma once

#include <concepts>
#include <iterator>
#include <math.h>
#include <numeric>
#include <vector>

namespace algo {
namespace detail {
template <class T> concept boolean_testable = std::convertible_to<T, bool>;

template <typename T>
concept partially_ordered = requires(const std::remove_reference_t<T> &lhs,
                                     const std::remove_reference_t<T> &rhs) {
  { lhs < rhs }
  ->boolean_testable;
  { rhs > lhs }
  ->boolean_testable;
};

template <typename Iter>
concept index_iter =
    std::forward_iterator<Iter> &&std::integral<std::iter_value_t<Iter>>;

template <typename Iter, typename Comp>
void insertion_sort(Iter begin, Iter end, Comp comp) {
  for (auto iter = begin; iter != end; ++iter) {
    for (auto cur_element = iter; cur_element != begin; --cur_element) {
      if (comp(*cur_element, *(cur_element - 1))) {
        std::swap(*cur_element, *(cur_element - 1));
      } else {
        break;
      }
    }
  }
}

template <typename Iter, typename ResultIter>
void radix_argsort_impl(Iter begin, Iter end, ResultIter result, int i) {
  auto size = std::distance(begin, end);
  auto bytes_count = sizeof(std::iter_value_t<Iter>);
  auto bits_count = bytes_count * 8;
  if (size < 2 || i >= bits_count) {
    return;
  }
  auto iter_begin = begin;
  auto iter_end = begin + size - 1;
  for (; iter_begin != iter_end;) {
    auto ith_greatest_bit_first = ((*iter_begin) >> ((bits_count - 1) - i)) & 1;
    auto ith_greatest_bit_second = ((*iter_end) >> ((bits_count - 1) - i)) & 1;
    if (ith_greatest_bit_first == 0) {
      ++iter_begin;
    } else if (ith_greatest_bit_second == 1) {
      --iter_end;
    } else {
      std::swap(*iter_begin, *iter_end);
      auto i = std::distance(begin, iter_begin);
      auto j = std::distance(begin, iter_end);
      std::swap(*(result + i), *(result + j));
    }
  }
  auto ith_greatest_bit_first = ((*iter_begin) >> ((bits_count - 1) - i)) & 1;
  if (ith_greatest_bit_first == 0) {
    ++iter_begin;
  }
  radix_argsort_impl(begin, iter_begin, result, i + 1);
  radix_argsort_impl(iter_begin, end, result, i + 1);
}
} // namespace detail

template <typename Iter, typename ResultIter>
void radix_argsort(Iter begin, Iter end,
                   ResultIter result) requires std::random_access_iterator<Iter>
    &&std::unsigned_integral<std::iter_value_t<Iter>>
        &&detail::index_iter<ResultIter> {
  std::vector tmp(begin, end);
  std::iota(result, result + std::distance(begin, end), 0);
  detail::radix_argsort_impl(tmp.begin(), tmp.end(), result, 0);
}

template <typename Iter, typename ResultIter>
void bucket_argsort(
    Iter begin, Iter end,
    ResultIter result) requires std::random_access_iterator<Iter>
    &&detail::partially_ordered<std::iter_value_t<Iter>>
        &&detail::index_iter<ResultIter> {
  auto num_buckets = (size_t)std::sqrt(std::distance(begin, end));
  auto max = *(std::max_element(begin, end));
  auto bucket_range = (uint64_t)ceil(((double)max) / num_buckets);
  using ValueType = std::iter_value_t<Iter>;
  using IndexType = std::iter_value_t<ResultIter>;
  using VIPair = std::pair<ValueType, IndexType>;
  std::vector<std::vector<VIPair>> buckets(num_buckets, std::vector<VIPair>());
  for (auto iter = begin; iter != end; iter++) {
    auto index = (int)floor((*iter / bucket_range));
    buckets[index].emplace_back(*iter, std::distance(begin, iter));
  }
  for (auto &bucket : buckets) {
    detail::insertion_sort(bucket.begin(), bucket.end(), std::less<VIPair>());
  }
  for (auto &bucket : buckets) {
    for (auto &pair : bucket) {
      *result = pair.second;
      ++result;
    }
  }
}

template <typename Iter, typename ResultIter>
void quick_argsort(Iter begin, Iter end,
                   ResultIter result) requires std::random_access_iterator<Iter>
    &&detail::partially_ordered<std::iter_value_t<Iter>>
        &&detail::index_iter<ResultIter> {}
} // namespace algo