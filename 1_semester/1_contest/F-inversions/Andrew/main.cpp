#include <iostream>
#include <iterator>

template <class T, class S = std::istream&>
void Input(T& value, S stream = std::cin) {
  stream >> value;
}
template <class T, class S = std::istream&>
void Input(T begin, T end, S stream = std::cin) {
  for (auto i = begin; i != end; ++i) {
    stream >> *i;
  }
}

template <class I>
size_t CountInversionsMerge(I begin, I end, I aux) {
  size_t result = 0;

  size_t size = std::distance(begin, end);

  auto mid = begin + size / 2;

  auto i1 = begin;
  auto i2 = mid;
  size_t i = 0;

  while (i1 != mid && i2 != end) {
    if (*i1 <= *i2) {
      aux[i++] = *(i1++);
    } else {
      aux[i++] = *(i2++);
      result += (mid - i1);
    }
  }

  while (i1 != mid) {
    aux[i++] = *(i1++);
  }

  for (size_t i = 0; i < size && begin + i != i2; ++i) {
    begin[i] = aux[i];
  }

  return result;
}

template <class I>
size_t CountInversions(I begin, I end, I aux) { 
  size_t result = 0;

  size_t size = std::distance(begin, end);

  if (size < 2) {
    return 0;
  }

  auto mid = begin + size / 2;

  result += CountInversions<I>(begin, mid, aux);

  result += CountInversions<I>(mid, end, aux);

  result += CountInversionsMerge<I>(begin, end, aux);

  return result;
}

template <class T = int, class I = T*>
size_t Inversions(I begin, I end) {
  auto aux_array = new T[end - begin];

  auto result = CountInversions<I>(begin, end, aux_array);

  delete[] aux_array;

  return result;
}

int main() {
  size_t n = 0;
  Input(n);

  auto array = new int[n];
  Input(array, array + n);

  std::cout << Inversions(array, array + n);

  delete[] array;
}