#include <iostream>
#include <algorithm>

namespace my {

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
I Min(I begin, I end) {
  if (end - begin == 0) {
    return nullptr;
  }
  I min = begin;
  for (auto it = begin + 1; it != end; ++it) {
    if (*it < *min) {
      min = it;
    }
  }
  return min;
}

}  // namespace my

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

struct CanNotFormGroups {};

// Checks if m groups with max difference less then diff can be formed
bool Check(size_t* differences, size_t diff, size_t n, size_t m, size_t k) {
  size_t groups_count = 0;
  size_t step = 0;

  for (size_t i = 0; i < n - k + 1; ++i) {
    if ((groups_count == 0 || step >= k) && differences[i] <= diff) {
      ++groups_count;
      if (groups_count == m) {
        return true;
      }
      step = 0;
    }
    ++step;
  }

  return false;
}

size_t Solution(size_t* people, size_t n, size_t m, size_t k) {
  if (m == 0 || k == 0) {
    return 0;
  }

  if (n < m * k) {
    throw CanNotFormGroups{};
  }

  size_t result = 0;

  my::Sort<size_t>(people, people + n);

  size_t differences_size = n - k + 1;
  auto differences = new size_t[differences_size];

  for (size_t i = 0; i < differences_size; ++i) {
    differences[i] = people[i + k - 1] - people[i];
  }

  if (m == 1) {
    result = *my::Min(differences, differences + differences_size);
  } else if (m > 1) {
    size_t min_diff = 0;
    size_t max_diff = people[n - 1] - people[0];
    size_t middle_diff = 0;

    while (min_diff != max_diff - 1) {
      middle_diff = (min_diff + max_diff) / 2;
      if (Check(differences, middle_diff, n, m, k) == 1) {
        max_diff = middle_diff;
      } else {
        min_diff = middle_diff;
      }
    }

    result = max_diff;
  }

  delete[] differences;
  return result;
}

int main() {
  size_t n = 0;  // amount of people
  size_t m = 0;  // amount of groups
  size_t k = 0;  // groups size

  std::cin >> n >> m >> k;

  auto people = new size_t[n];
  Input(people, people + n);

  std::cout << Solution(people, n, m, k);

  delete[] people;

  return 0;
}