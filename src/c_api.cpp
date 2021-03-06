#include "algo/c_api.h"
#include "algo/experimental_sort.hpp"
#include "algo/sorting.hpp"

void radix_argsort_u64(uint64_t *arr, uint64_t *indices, uint64_t size) {
  algo::radix_argsort(arr, arr + size, indices);
}
void experimental_radix_argsort_u64(uint64_t *arr, uint64_t *indices,
                                    uint64_t size) {
  algo::experimental::radix_argsort(arr, arr + size, indices);
}
void bucket_argsort_u64(uint64_t *arr, uint64_t *indices, uint64_t size) {
  algo::bucket_argsort(arr, arr + size, indices);
}
void quick_argsort_u64(uint64_t *arr, uint64_t *indices, uint64_t size) {
  algo::quick_argsort(arr, arr + size, indices);
}
