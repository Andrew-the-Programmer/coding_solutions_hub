#pragma once

#include <iterator>

template <class T, class I = const T*>
I LowerBound(I begin, I end, const T& value) {
  if (!begin || !end) {
    return nullptr;
  }

  auto left = begin;
  auto right = end;
  size_t size = 0;
  I mid = nullptr;

  while (true) {
    size = std::distance(left, right);

    if (size == 0 || value < *left) {
      return right;
    }
    if (*(right - 1) < value) {
      return end;
    }
    if (size == 1) {
      return left;
    }

    mid = left + (size / 2);

    if (value < *mid) {
      right = mid;
    } else {
      left = mid;
    }
  }
}

template <class T, class I>
bool BinarySearch(I begin, I end, const T& value) {
  auto ptr = LowerBound<T, I>(begin, end, value);
  return !(ptr == end || value < *ptr);
}

template <class T, class I>
I UpperBound(I begin, I end, const T& value) {
  auto ptr = LowerBound<T, I>(begin, end, value);
  if (ptr == end || value < *ptr)
    return ptr;
  return ptr + 1;
}