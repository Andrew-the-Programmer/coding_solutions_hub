#pragma once

#include <cstdint>
#include <iostream>

template <class T, class I, class Cmp = std::less<T>>
void Merge(I begin, I mid, I end, I aux, Cmp cmp = Cmp()) {
  auto i1 = begin;
  auto i2 = mid;
  auto i = 0;
  while (i1 != mid && i2 != end) {
    if (cmp(*i1, *i2)) {
      aux[i++] = *(i1++);
    } else {
      aux[i++] = *(i2++);
    }
  }
  while (i1 != mid) {
    aux[i++] = *(i1++);
  }
  for (auto it = begin; it != i2; ++it) {
    *it = *(aux++);
  }
}

template <class T, class I, class Cmp = std::less<T>>  // O(n*log(n))
void MergeSort(I begin, I end, I aux, Cmp cmp = Cmp()) {
  size_t size = end - begin;
  if (size < 2) {
    return;
  }
  auto mid = begin + size/2;
  MergeSort<T,I,Cmp>(begin, mid, aux, cmp);
  MergeSort<T,I,Cmp>(mid, end, aux, cmp);
  Merge<T,I,Cmp>(begin, mid, end, aux, cmp);
}

template <class T = int, class I = T*, class Cmp = std::less<T>>
void Sort(I begin, I end, Cmp cmp = Cmp()) {
  I aux = new T[end - begin];
  MergeSort<T,I,Cmp>(begin, end, aux, cmp);
  delete[] aux;
}