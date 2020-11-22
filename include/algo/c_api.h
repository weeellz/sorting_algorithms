#pragma once
#include <cstdint>

extern "C" {
void radix_argsort_u64(uint64_t *arr, uint64_t *indices, uint64_t size);
void bucket_argsort_u64(uint64_t *arr, uint64_t *indices, uint64_t size);
void quick_argsort_u64(uint64_t *arr, uint64_t *indices, uint64_t size);
}