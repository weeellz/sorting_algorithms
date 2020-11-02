#pragma once

#include <concepts>
#include <iterator>

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
} // namespace detail

template <typename Iter>
void radix_argsort(Iter begin, Iter end, Iter ibegin,
                   Iter iend) requires std::random_access_iterator<Iter>
    &&std::unsigned_integral<std::iter_value_t<Iter>> {}

template <typename Iter>
void bucket_argsort(Iter begin, Iter end, Iter ibegin,
                    Iter iend) requires std::random_access_iterator<Iter>
    &&detail::partially_ordered<std::iter_value_t<Iter>> {}

template <typename Iter>
void quick_argsort(Iter begin, Iter end, Iter ibegin,
                   Iter iend) requires std::random_access_iterator<Iter>
    &&detail::partially_ordered<std::iter_value_t<Iter>> {}
} // namespace algo