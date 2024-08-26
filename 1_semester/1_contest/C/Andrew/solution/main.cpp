#include <iostream>
#include <algorithm>

template <class T, class S = std::ostream&>
void Put(const T& value, S stream = std::cout) {
  stream << value << std::endl;
}

template <class T, class S = std::ostream&>
void Put(const T begin, const T end, S stream = std::cout) {
  for (auto i = begin; i != end; ++i) {
    stream << *i << " ";
  }
  stream << std::endl;
}

template <class T, class S = std::istream&>
void Get(T& value, S stream = std::cin) {
  stream >> value;
}

template <class T, class S = std::istream&>
void Get(T begin, T end, S stream = std::cin) {
  for (auto i = begin; i != end; ++i) {
    stream >> *i;
  }
}

template <class T>
auto Check(T* arr1, size_t size1, T* arr2, size_t size2) {

  if (size1 == 0 && size2 == 0) {
    return "YES";
  }
  if (size1 == 0 || size2 == 0 || arr1[0] != arr2[0]) {
    return "NO";
  }

  size_t i1 = 0;
  size_t i2 = 0;

  while (i1 < size1 - 1 && arr1[i1] == arr1[i1 + 1]) {
    ++i1;
  }
  while (i2 < size2 - 1 && arr2[i2] == arr2[i2 + 1]) {
    ++i2;
  }

  return Check(arr1 + i1 + 1, size1 - i1 - 1, arr2 + i2 + 1, size2 - i2 - 1);
}

int main() {
  size_t n1 = 0;
  size_t n2 = 0;

  Get(n1);

  int* arr1 = new int[n1];

  Get(arr1, arr1 + n1);

  Get(n2);

  int* arr2 = new int[n2];

  Get(arr2, arr2 + n2);

  std::sort(arr1, arr1 + n1);
  std::sort(arr2, arr2 + n2);

  std::cout << Check(arr1, n1, arr2, n2);

  delete[] arr1;
  delete[] arr2;

  return 0;
}