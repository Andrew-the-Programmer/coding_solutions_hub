#include <stdexcept>
#include <algorithm>

#include <iostream>

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

template <class T, class I = const T*>
I LowerBound(I begin, I end, const T& value) {
  if (!begin || !end) {
    return nullptr;
  }

  size_t size = end - begin;
  I mid = begin + size / 2;

  if (size == 0 || value < *begin) {
    return begin;
  }
  if (!(value < *(end - 1))) {
    return end;
  }
  if (size == 1) {
    return begin;
  }

  if (*begin < *mid) {
    return LowerBound(begin, mid, value);
  }
  return LowerBound(mid, end, value);
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

}  // namespace my

struct SomethingWentWrong {};

template <class T>
class DynArray {
 public:
  DynArray() : capacity_(0), size_(0), data_(nullptr) {
  }
  explicit DynArray(size_t capacity) : capacity_(capacity), size_(0), data_(new T[capacity]) {
  }
  DynArray(size_t size, const T& def_value) : capacity_(2*size), size_(size), data_(new T[capacity]) {
    std::fill(data_, data_ + size_, def_value);
  }
  ~DynArray() {
    delete[] data_;
  }

 public:
  const T& At(size_t index) const {
    if (index < size_) {
      return data_[index];
    }
    throw std::out_of_range{""};
  }
  T& At(size_t index) {
    if (index < size_) {
      return data_[index];
    }
    throw std::out_of_range{""};
  }

  size_t Size() const {
    return size_;
  }

  void PushBack(const T& value) {
    if (size_ < capacity_) {
      data_[size_++] = value;
    } else {
      throw SomethingWentWrong{};
    }
  }

  const T* begin() const {  // NOLINT
    return data_;
  }
  T* begin() {  // NOLINT
    return data_;
  }
  const T* end() const {  // NOLINT
    return data_ + size_;
  }
  T* end() {  // NOLINT
    return data_ + size_;
  }

 protected:
  size_t capacity_;
  size_t size_;
  T* data_;
};

struct GroupOfSections {
  size_t length = 0;
  size_t amount = 0;

  size_t FullLength() const {
    return length * amount;
  }

  bool IsSingle() const {
    return amount == 1;
  }

  bool operator<(const GroupOfSections& other) const {
    return length < other.length;
  }

  friend bool operator<(size_t length, const GroupOfSections& g) {
    return length < g.length;
  }
};

class Sections : public DynArray<GroupOfSections> {
 public:
  Sections() = default;
  explicit Sections(size_t capacity) : DynArray(capacity) {
  }

 public:
  size_t SingleLength(size_t index) const {
    return At(index).length;
  }

  size_t Length(size_t index) const {
    return At(index).FullLength();
  }

  size_t Length(size_t from, size_t to) const {
    size_t result = 0;
    for (size_t i = from; i < to; ++i) {
      result += Length(i);
    }
    return result;
  }

  size_t FullLength() const {
    return Length(0, Size());
  }

  size_t CountSections(size_t from, size_t to) const {
    size_t result = 0;
    for (size_t i = from; i < to; ++i) {
      result += At(i).amount;
    }
    return result;
  }

  size_t CountAllSections() const {
    return CountSections(0, Size());
  }

  size_t UpperBound(size_t from, size_t to, size_t length) const {
    return my::UpperBound(begin() + from, begin() + to, length) - begin();
  }

 public:
  std::pair<size_t, size_t> Solution() const {
    if (Size() < 2) {
      return {CountAllSections(), FullLength()};
    }

    size_t max_amount_of_sections = 0;
    size_t max_length = 0;

    size_t length = 0;
    size_t length_limit = 0;
    size_t to = 0;

    for (size_t from = 0; from < Size() - 1; ++from) {
      length_limit = SingleLength(from) + SingleLength(from + 1);

      to = UpperBound(from + 2, Size(), length_limit);

      length = SingleLength(from) + Length(from + 1, to);

      if (length > max_length) {
        max_length = length;
        max_amount_of_sections = 1 + CountSections(from + 1, to);
      }

      if (!At(from).IsSingle()) {
        length_limit = 2 * SingleLength(from);

        to = UpperBound(from + 1, Size(), length_limit);

        length = Length(from, to);

        if (length > max_length) {
          max_length = length;
          max_amount_of_sections = CountSections(from, to);
        }
      }
    }
    return {max_amount_of_sections, max_length};
  }
};

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

int main() {
  size_t n = 0;
  Input(n);

  auto array = new size_t[n];
  Input(array, array + n);

  Sections sections(n);

  my::Sort<size_t>(array, array + n);

  size_t count = 0;
  for (size_t i = 0; i < n; ++i) {
    if (i == n - 1 || array[i] != array[i + 1]) {
      sections.PushBack({array[i], count + 1});
      count = 0;
    } else {
      ++count;
    }
  }

  auto answer = sections.Solution();

  std::cout << answer.first << " " << answer.second;

  delete[] array;
}