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

  auto mid = begin + size / 2;

  MergeSort<T, I, Cmp>(begin, mid, aux, cmp);
  MergeSort<T, I, Cmp>(mid, end, aux, cmp);
  Merge<T, I, Cmp>(begin, mid, end, aux, cmp);
}

template <class T, class I = T*, class Cmp = std::less<T>>
void Sort(I begin, I end, Cmp cmp = Cmp()) {
  I aux = new T[end - begin];
  MergeSort<T, I, Cmp>(begin, end, aux, cmp);
  delete[] aux;
}

template <class I>
void InputRange(I begin, I end) {
  for (auto it = begin; it != end; ++it) {
    std::cin >> *it;
  }
}

template <class T>
T InputResult() {
  T value;
  std::cin >> value;
  return value;
}

size_t Solution(size_t size, size_t* array) {
  if (size < 2) {
    return 0;
  }

  Sort<size_t>(array, array + size);

  auto dp = new size_t[size]{};

  for (size_t i = 0; i < size; ++i) {
    if (i < 3) {
      dp[i] = array[i] - array[0];
    } else if (i == 3) {
      dp[i] = dp[i - 2] + array[i] - array[i - 1];
    } else {
      dp[i] = std::min(dp[i - 2] + array[i] - array[i - 1], dp[i - 3] + array[i] - array[i - 2]);
    }
  }

  size_t result = dp[size - 1];
  delete[] dp;
  return result;
}

int main() {
  size_t n = 0;
  std::cin >> n;

  auto array = new size_t[n];
  InputRange(array, array + n);

  std::cout << Solution(n, array);

  delete[] array;
}