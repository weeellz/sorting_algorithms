#pragma once

#include <concepts>
#include <iterator>
#include <math.h>
#include <numeric>
#include <random>
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
        std::iter_swap(cur_element, cur_element - 1);
      } else {
        break;
      }
    }
  }
}

template <typename Iter, typename ResultIter, typename Comp>
void insertion_argsort_impl(Iter begin, Iter end, ResultIter result,
                            Comp comp) {
  for (auto iter = begin; iter != end; ++iter) {
    for (auto cur_element = iter; cur_element != begin; --cur_element) {
      if (comp(*cur_element, *(cur_element - 1))) {
        std::iter_swap(cur_element, cur_element - 1);
        auto i = std::distance(begin, cur_element);
        auto j = std::distance(begin, cur_element - 1);
        std::iter_swap(result + i, result + j);
      } else {
        break;
      }
    }
  }
}

template <typename Iter, typename ResultIter>
void counting_argsort_impl(Iter begin, Iter end, ResultIter result,
                           std::iter_value_t<Iter> max) {
  auto size = std::distance(begin, end);

  std::vector<int> counts_array(max + 1, 0);
  for (auto iter = begin; iter != end; ++iter) {
    ++counts_array[*iter];
  }

  for (int i = 1; i < max + 1; ++i) {
    counts_array[i] += counts_array[i - 1];
  }

  for (int i = size - 1; i >= 0; --i) {
    auto original_number = *(begin + i);
    auto pos = counts_array[original_number] - 1;
    result[pos] = i;
    --counts_array[original_number];
  }
}

template <typename Iter, typename ResultIter>
void radix_argsort_impl(Iter begin, Iter end, ResultIter result) {
  if (std::distance(begin, end) < 2) {
    return;
  }

  auto bits_count = sizeof(std::iter_value_t<Iter>) * 8;
  auto bits_per_loop = 0;

  switch (bits_count) {
  case 8:
  case 16:
    bits_per_loop = bits_count;
    break;
  case 32:
    bits_per_loop = bits_count / 2;
    break;
  case 64:
    bits_per_loop = bits_count / 4;
    break;
  }

  auto loops = bits_count / bits_per_loop;
  auto mask = (1 << bits_per_loop) - 1;
  std::vector<size_t> counts(1 << bits_per_loop);
  std::vector<std::iter_value_t<Iter>> temp(std::distance(begin, end));
  std::vector<std::iter_value_t<ResultIter>> temp_indices(
      std::distance(begin, end));

  for (int p = 0; p < loops; ++p) {
    std::fill(counts.begin(), counts.end(), 0);
    std::copy(result, result + std::distance(begin, end), temp_indices.begin());

    for (auto iter = begin; iter != end; ++iter) {
      auto cur_bits = ((*iter) >> (bits_per_loop * p)) & mask;
      ++counts[cur_bits];
    }

    for (int i = 1; i < counts.size(); ++i) {
      counts[i] += counts[i - 1];
    }

    for (int i = std::distance(begin, end) - 1; i >= 0; --i) {
      auto num = *(begin + i);
      auto cur_bits = (num >> (bits_per_loop * p)) & mask;
      auto pos = counts[cur_bits] - 1;
      temp[pos] = num;
      *(result + pos) = temp_indices[i];
      --counts[cur_bits];
    }
    std::copy(temp.begin(), temp.end(), begin);
  }
}

template <typename Iter, typename ResultIter>
std::pair<Iter, Iter> partition(Iter begin, Iter end, ResultIter result,
                                int random) {

  auto pivot = *(begin + random);
  auto left = begin;
  auto right = begin;
  auto upper_bound = begin + std::distance(begin, end) - 1;

  while (std::distance(begin, right) <= std::distance(begin, upper_bound)) {
    if (*right < pivot) {
      std::iter_swap(left, right);
      std::iter_swap(result + std::distance(begin, left),
                     result + std::distance(begin, right));
      ++left;
      ++right;
    } else if (*right > pivot) {
      std::iter_swap(right, upper_bound);
      std::iter_swap(result + std::distance(begin, right),
                     result + std::distance(begin, upper_bound));
      --upper_bound;
    } else {
      ++right;
    }
  }

  return {left, right};
}

template <typename Iter, typename ResultIter, int Limit = 100>
void quick_argsort_impl(Iter begin, Iter end, ResultIter result,
                        std::mt19937 &generator) {
  for (auto size = std::distance(begin, end); size >= Limit;
       size = std::distance(begin, end)) {
    std::uniform_int_distribution<int> distribution(0, size);
    auto random = distribution(generator);
    auto [l, r] = detail::partition(begin, end, result, random);
    if (std::distance(begin, l) <= std::distance(r, end)) {
      quick_argsort_impl(begin, l, result, generator);
      result += std::distance(begin, r);
      begin = r;
    } else {
      quick_argsort_impl(r, end, result + std::distance(begin, r), generator);
      end = l;
    }
  }
  detail::insertion_argsort_impl(begin, end, result, std::less());
}
} // namespace detail

template <typename Iter, typename ResultIter, typename Comp>
void insertion_argsort(Iter begin, Iter end, ResultIter result,
                       Comp comp) requires std::random_access_iterator<Iter>
    &&std::unsigned_integral<std::iter_value_t<Iter>>
        &&detail::index_iter<ResultIter> {
  auto size = std::distance(begin, end);
  if (size < 2) {
    return;
  }
  std::vector tmp(begin, end);
  std::iota(result, result + std::distance(begin, end), 0);
  detail::insertion_argsort_impl(tmp.begin(), tmp.end(), result, comp);
}

template <typename Iter, typename ResultIter>
void counting_argsort(
    Iter begin, Iter end,
    ResultIter result) requires std::random_access_iterator<Iter>
    &&std::unsigned_integral<std::iter_value_t<Iter>>
        &&detail::index_iter<ResultIter> {
  auto size = std::distance(begin, end);
  if (size < 2) {
    return;
  }
  std::vector tmp(begin, end);
  auto max = *(std::max_element(tmp.begin(), tmp.end()));
  detail::counting_argsort_impl(tmp.begin(), tmp.end(), result, max);
}

template <typename Iter, typename ResultIter>
void radix_argsort(Iter begin, Iter end,
                   ResultIter result) requires std::random_access_iterator<Iter>
    &&std::unsigned_integral<std::iter_value_t<Iter>>
        &&detail::index_iter<ResultIter> {
  std::vector tmp(begin, end);
  std::iota(result, result + std::distance(begin, end), 0);
  detail::radix_argsort_impl(tmp.begin(), tmp.end(), result);
}

template <typename Iter, typename ResultIter>
void bucket_argsort(
    Iter begin, Iter end,
    ResultIter result) requires std::random_access_iterator<Iter>
    &&detail::partially_ordered<std::iter_value_t<Iter>>
        &&detail::index_iter<ResultIter> {
  auto size = std::distance(begin, end);
  if (size < 2) {
    return;
  }
  auto num_buckets = std::distance(begin, end);
  auto max = *(std::max_element(begin, end));
  auto bucket_range = (uint64_t)ceil(((double)max) / num_buckets);
  using ValueType = std::iter_value_t<Iter>;
  using IndexType = std::iter_value_t<ResultIter>;
  using VIPair = std::pair<ValueType, IndexType>;
  std::vector<std::vector<VIPair>> buckets(num_buckets + 1,
                                           std::vector<VIPair>());
  for (auto iter = begin; iter != end; ++iter) {
    if (*iter == 0) {
      buckets[0].emplace_back(*iter, std::distance(begin, iter));
    } else {
      auto index = (int)floor((*iter / bucket_range));
      buckets[index].emplace_back(*iter, std::distance(begin, iter));
    }
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

template <typename Iter, typename ResultIter, int Limit = 100>
void quick_argsort(Iter begin, Iter end,
                   ResultIter result) requires std::random_access_iterator<Iter>
    &&detail::partially_ordered<std::iter_value_t<Iter>>
        &&detail::index_iter<ResultIter> {
  static thread_local std::mt19937 generator(std::random_device{}());

  std::vector tmp(begin, end);
  std::iota(result, result + std::distance(begin, end), 0);
  detail::quick_argsort_impl<decltype(tmp.begin()), decltype(result), Limit>(
      tmp.begin(), tmp.end(), result, generator);
}
} // namespace algo