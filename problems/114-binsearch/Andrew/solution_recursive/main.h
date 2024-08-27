#pragma once

#include <iterator>

template <class T, class I = const T*>
I LowerBound(I begin, I end, const T& value) {
  size_t size = std::distance(begin, end);
  if (size == 0 || value < *begin || !(*begin < value)) {
    return begin;
  }
  if (*(end - 1) < value) {
    return end;
  }
  auto mid = begin + (size / 2);
  if (value < *mid) {
    return LowerBound<T, I>(begin, mid, value);
  }
  return LowerBound<T, I>(mid, end, value);
}

template <class T, class I>
bool BinarySearch(I begin, I end, const T& value) {
  auto ptr = LowerBound<T, I>(begin, end, value);
  return !(ptr == end || value < *ptr);
}

template <class T, class I>
I UpperBound(I begin, I end, const T& value) {
  auto ptr = LowerBound<T, I>(begin, end, value);
  if (ptr == end || value < *ptr) {
    return ptr;
  }
  return ptr + 1;
}
