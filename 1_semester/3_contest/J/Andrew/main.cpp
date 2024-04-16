#include <iostream>

struct DynArrayIsEmpty {};

template <class T>
class DynArray {
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
  DynArray(const std::initializer_list<T> list) : DynArray(list.size(), T()) {
    std::copy(list.begin(), list.end(), begin());
  }
  DynArray(const DynArray& other) : DynArray(other.Size(), other.Capacity(), new T[other.Capacity()]) {
    std::copy(other.begin(), other.end(), begin());
  }

  ~DynArray() {
    delete[] data_;
  }

 public:
  DynArray& operator=(const DynArray& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new T[capacity_];
    std::copy(other.begin(), other.end(), data_);
    return *this;
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

  bool IsEmpty() const {
    return Size() == 0;
  }

  void ThrowIfEmpty() const {
    if (IsEmpty()) {
      throw DynArrayIsEmpty{};
    }
  }

 public:
  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return capacity_;
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

  void Output() const {
    for (auto val : *this) {
      std::cout << val << ' ';
    }
  }

  void Input() {
    T value = T();
    for (size_t i = Size(); i < Capacity(); ++i) {
      std::cin >> value;
      PushBack(value);
    }
  }

  T Min() const {
    ThrowIfEmpty();
    T min = At(0);
    for (size_t i = 1; i < Size(); ++i) {
      if (At(i) < min) {
        min = At(i);
      }
    }
    return min;
  }

  T Max() const {
    ThrowIfEmpty();
    T max = 0;
    for (size_t i = 0; i < Size(); ++i) {
      if (At(i) > max) {
        max = At(i);
      }
    }
    return max;
  }

  T Sum() const {
    T sum = 0;
    for (size_t i = 0; i < Size(); ++i) {
      sum += At(i);
    }
    return sum;
  }

 protected:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T* data_ = nullptr;
};

template <class T>
size_t Solution(const DynArray<T>& array) {
  if (array.Size() == 0) {
    return 0;
  }
  T min = array.Min();
  T max = array.Max();
  size_t size = max - min + 1;
  DynArray<size_t> dp(size, 0);  // dp[array[i] - min] - amount of increasing subsequanses ending in array[i]
  for (size_t i = 0; i < array.Size(); ++i) {
    size_t index = array[i] - min;
    dp[index] += 1;
    for (size_t j = 0; j < index; ++j) {
      dp[index] += dp[j];
    }
    dp[index] %= 1000000;
  }
  return dp.Sum();
}

using T = int64_t;

int main() {
  size_t n = 0;
  std::cin >> n;
  DynArray<T> array(n);
  array.Input();
  std::cout << Solution(array) % 1000000;
}