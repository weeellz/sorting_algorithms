#pragma once
#include <cstdint>

extern "C" {
void radix_argsort_u16(uint16_t *arr, uint16_t *indices, uint64_t size);
void bucket_argsort_u16(uint16_t *arr, uint16_t *indices, uint64_t size);
void quick_argsort_u16(uint16_t *arr, uint16_t *indices, uint64_t size);
}