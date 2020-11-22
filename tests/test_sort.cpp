#include <algo/sorting.hpp>
#include <algorithm>
#include <gtest/gtest.h>
#include <numeric>

template <typename T> class SortTest : public ::testing::Test {
protected:
  std::vector<std::vector<T>> data;

  std::vector<size_t> get_sorted_indices(const std::vector<T> &v) {
    std::vector<size_t> result(v.size());
    std::iota(result.begin(), result.end(), 0);
    std::sort(result.begin(), result.end(),
              [&](auto lhs, auto rhs) { return v[lhs] < v[rhs]; });
    return result;
  }

  std::vector<size_t> get_sorted_array(const std::vector<T> &v) {
    std::vector<size_t> result(v.begin(), v.end());
    std::sort(result.begin(), result.end());
    return result;
  }

  void SetUp() override {
    data = {{},
            {8},
            {2, 1},
            {1, 3, 2},
            {5, 3, 6, 1, 4, 3},
            {50, 1, 15, 6, 30, 7, 18},
            {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {7, 1, 5, 9, 10, 25, 3, 18, 1, 67, 4, 6, 2, 4},
            {5, 5, 5, 5, 5, 5, 5},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  }
};

using unsigned_types = ::testing::Types<uint8_t, uint16_t, uint32_t, uint64_t>;

template <typename ValueType>
void print(std::vector<ValueType> const &array, std::string const &str) {
  std::cout << std::endl;
  std::cout << str;
  for (int i = 0; i < array.size(); ++i) {
    std::cout << array[i] << " ";
  }
}

template <typename ValueType, typename IndexType>
void print(std::vector<ValueType> const &array,
           std::vector<IndexType> const &indices, std::string const &str) {
  std::cout << std::endl;
  std::cout << str;
  for (int i = 0; i < array.size(); ++i) {
    std::cout << (int)array[indices[i]] << " ";
  }
}

TYPED_TEST_SUITE(SortTest, unsigned_types);

TYPED_TEST(SortTest, insertion_sort_test) {
  for (auto &v : this->data) {
    auto expected = this->get_sorted_array(v);
    std::vector<size_t> actual(v.size());
    algo::insertion_argsort(v.begin(), v.end(), actual.begin(), std::less());

    print(expected, "Expected array: ");
    print(v, actual, "Sorted array: ");
    // print(expected, "Expected indices: ");
    // print(actual, "Sorted indices: ");

    std::cout << std::endl;
    for (int i = 0; i < v.size(); ++i) {
      EXPECT_EQ(expected[i], v[actual[i]]) << "Different values at " << i;
    }
  }
}

TYPED_TEST(SortTest, counting_sort_test) {
  for (auto &v : this->data) {
    auto expected = this->get_sorted_array(v);
    std::vector<size_t> actual(v.size());
    algo::counting_argsort(v.begin(), v.end(), actual.begin());

    print(expected, "Expected array: ");
    print(v, actual, "Sorted array: ");
    // print(expected, "Expected indices: ");
    // print(actual, "Sorted indices: ");

    std::cout << std::endl;
    for (int i = 0; i < v.size(); ++i) {
      EXPECT_EQ(expected[i], v[actual[i]]) << "Different values at " << i;
    }
  }
}

TYPED_TEST(SortTest, quick_sort_test) {
  for (auto &v : this->data) {
    auto expected = this->get_sorted_array(v);
    std::vector<size_t> actual(v.size());
    algo::quick_argsort<decltype(v.begin()), decltype(actual.begin()), 7>(
        v.begin(), v.end(), actual.begin());

    print(expected, "Expected array: ");
    print(v, actual, "Sorted array: ");

    std::cout << std::endl;
    for (int i = 0; i < v.size(); ++i) {
      EXPECT_EQ(expected[i], v[actual[i]]) << "Different values at " << i;
    }
  }
}

TYPED_TEST(SortTest, radix_sort_test) {
  for (auto &v : this->data) {
    auto expected = this->get_sorted_array(v);
    std::vector<size_t> actual(v.size());
    algo::radix_argsort(v.begin(), v.end(), actual.begin());

    print(expected, "Expected array: ");
    print(v, actual, "Sorted array: ");
    // print(expected, "Expected indices: ");
    // print(actual, "Sorted indices: ");

    std::cout << std::endl;
    for (int i = 0; i < v.size(); ++i) {
      EXPECT_EQ(expected[i], v[actual[i]]) << "Different values at " << i;
    }
  }
}

TYPED_TEST(SortTest, bucket_sort_test) {
  for (auto &v : this->data) {
    auto expected = this->get_sorted_array(v);
    std::vector<size_t> actual(v.size());
    algo::bucket_argsort(v.begin(), v.end(), actual.begin());

    print(expected, "Expected array: ");
    print(v, actual, "Sorted array: ");
    // print(expected, "Expected indices: ");
    // print(actual, "Sorted indices: ");

    std::cout << std::endl;
    for (int i = 0; i < v.size(); ++i) {
      EXPECT_EQ(expected[i], v[actual[i]]) << "Different values at " << i;
    }
  }
}