#include "algo/sorting.hpp"
#include <iostream>

int main() {
  std::vector<uint32_t> v = {1, 3, 2, 7, 5, 4, 3, 9};
  // std::vector<uint32_t> v = {1, 4, 3, 2};
  std::vector<uint32_t> result(v.size());
  algo::radix_argsort(v.begin(), v.end(), result.begin());
  for (auto element : v) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
  for (auto element : result) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
  for (auto element : result) {
    std::cout << v[element] << " ";
  }
  std::cout << std::endl;
}