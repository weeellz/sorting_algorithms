#include "algo/sorting.hpp"
#include <iostream>
#include <iterator>

int main() {
  std::vector<int> v = {1, 3, 2, 7, 5, 4, 3, 9};
  std::vector<int> result(v.size());
  algo::bucket_argsort(v.begin(), v.end(), result.begin());
  for (auto element : result) {
    std::cout << v[element] << std::endl;
  }
}