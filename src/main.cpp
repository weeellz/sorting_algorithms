#include "algo/sorting.hpp"
#include <iostream>
#include <iterator>

template <typename Iter, typename ResultIter>
void radix_argsort(Iter begin, Iter end, ResultIter result, int i) {
  auto bytes_count = sizeof(std::iter_value_t<Iter>);
  auto bits_count = bytes_count * 8;
  if (std::distance(begin, end) < 2 || i >= bits_count) {
    return;
  }
  auto iter_begin = begin;
  auto iter_end = begin + std::distance(begin, end) - 1;
  for (; iter_begin != iter_end;) {
    auto bytes_count = sizeof(std::iter_value_t<Iter>);
    auto bits_count = bytes_count * 8;
    auto first = *iter_begin;
    auto second = *iter_end;
    auto ith_greatest_bit_first = ((*iter_begin) >> ((bits_count - 1) - i)) & 1;
    auto ith_greatest_bit_second = ((*iter_end) >> ((bits_count - 1) - i)) & 1;
    if (ith_greatest_bit_first == 0) {
      ++iter_begin;
    } else if (ith_greatest_bit_second == 1) {
      --iter_end;
    } else {
      std::swap(*iter_begin, *iter_end);
    }
  }
  auto ith_greatest_bit_first = ((*iter_begin) >> ((bits_count - 1) - i)) & 1;
  if (ith_greatest_bit_first == 0) {
    ++iter_begin;
  }
  radix_argsort(begin, iter_begin, result, i + 1);
  radix_argsort(iter_begin, end, result, i + 1);
}

int main() {
  // std::vector<int> v = {1, 3, 2, 7, 5, 4, 3, 9};
  int i = 0;
  std::vector<int> v = {1, 4, 3, 2};
  std::vector<int> result(v.size());
  radix_argsort(v.begin(), v.end(), result.begin(), i);
  for (auto element : v) {
    std::cout << element << std::endl;
  }
  // for (auto element : result) {
  //   std::cout << v[element] << std::endl;
  // }
}