#include <iostream>
#include <iterator>

template <class T, class I = const T*>
I LowerBound(I begin, I end, const T& value) {
  size_t size = std::distance(begin, end);
  if (size == 0 || value <= *begin) {
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

template <class T>
T InputResult() {
  T value;
  std::cin >> value;
  return value;
}

template <class T>
class DynArray {
  using Iterator = T*;
  using ConstIterator = const T*;

 protected:
  DynArray(size_t size, size_t capacity, T* data) : size_(size), capacity_(capacity), data_(data) {
  }

 public:
  DynArray() : DynArray(0, 0, nullptr) {
  }
  explicit DynArray(size_t capacity) : DynArray(0, capacity, new T[capacity]) {
  }
  DynArray(size_t size, const T& def_value) : DynArray(size, 2 * size, new T[2 * size]) {
    std::fill(data_, data_ + size_, def_value);
  }
  DynArray(const DynArray& other) : DynArray(other.Size(), other.Capacity(), new T[other.Capacity()]) {
    std::copy(other.begin(), other.end(), begin());
  }

  DynArray& operator=(const DynArray& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new T[capacity_];
    std::copy(other.begin(), other.end(), data_);
    return *this;
  }

  ~DynArray() {
    delete[] data_;
  }

 protected:
  bool IsInBounds(size_t index) const {
    return index < Size();
  }

  void ThrowIfOutOfRange(size_t index) const {
    if (!IsInBounds(index)) {
      throw std::out_of_range{""};
    }
  }

 public:
  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return capacity_;
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

  const T& At(size_t index) const {
    ThrowIfOutOfRange(index);
    return data_[index];
  }

  T& At(size_t index) {
    ThrowIfOutOfRange(index);
    return data_[index];
  }

  const T& operator[](size_t index) const {
    return data_[index];
  }

  T& operator[](size_t index) {
    return data_[index];
  }

  void PushBack(const T& value) {
    if (size_ < capacity_) {
      data_[size_++] = value;
    }
  }

  void Replace(Iterator iter, const T& value) {
    if (iter == end()) {
      PushBack(value);
      return;
    }
    int64_t index = iter - begin();
    At(index) = value;
  }

  void Output() const {
    for (auto val : *this) {
      std::cout << val << ' ';
    }
  }

  void Input() {
    for (size_t i = Size(); i < Capacity(); ++i) {
      PushBack(InputResult<T>());
    }
  }

 protected:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T* data_ = nullptr;
};

template <class T>
auto Lis(const DynArray<T>& array) {
  size_t size = array.Size();

  if (size == 0) {
    return DynArray<T>();
  }

  DynArray<T> dp(size);
  DynArray<size_t> pos(size, 0);
  DynArray<size_t> prev(size, 0);

  for (size_t i = 0; i < size; ++i) {
    auto insert_iter = LowerBound(dp.begin(), dp.end(), array[i]);
    size_t insert_index = insert_iter - dp.begin();
    dp.Replace(insert_iter, array[i]);
    pos[insert_index] = i;
    if (insert_index > 0) {
      prev[i] = pos[insert_index - 1];
    }
  }

  DynArray<T> result(dp.Size(), T());

  size_t res_index = dp.Size();
  size_t index = pos[dp.Size() - 1];

  for (; res_index > 0; index = prev[index]) {
    result[--res_index] = array[index];
  }

  return result;
}

template <class T>
void Solution(const DynArray<T>& array) {
  std::cout << Lis(array).Size();
}

using T = int64_t;

int main() {
  DynArray<T> array(InputResult<size_t>());
  array.Input();

  Solution(array);
}