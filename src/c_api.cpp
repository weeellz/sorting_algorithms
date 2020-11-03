#include "algo/c_api.h"
#include "algo/sorting.hpp"

void radix_argsort_u16(uint16_t *arr, uint16_t *indices, uint64_t size) {
  algo::radix_argsort(arr, arr + size, indices);
}
void bucket_argsort_u16(uint16_t *arr, uint16_t *indices, uint64_t size) {
  algo::bucket_argsort(arr, arr + size, indices);
}
void quick_argsort_u16(uint16_t *arr, uint16_t *indices, uint64_t size) {
  algo::bucket_argsort(arr, arr + size, indices);
}
