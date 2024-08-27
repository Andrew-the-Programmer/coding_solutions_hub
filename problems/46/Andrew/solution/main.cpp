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
struct Optional {
  class ValueIsUndefined {};

 protected:
  bool undefined = true;
  T value = 0;

 public:
  bool IsUndefined() const {
    return undefined;
  }

  bool IsDefined() const {
    return !IsUndefined();
  }

 protected:
  void ThrowIfUndefined() const {
    if (IsUndefined()) {
      throw ValueIsUndefined{};
    }
  }

 public:
  void Set(const T& value) {
    this->value = value;
    undefined = false;
  }

  const T& Get() const {
    ThrowIfUndefined();
    return value;
  }
};

template <class T>
using D = DynArray<T>;

template <class T>
using D2 = DynArray<D<T>>;

template <class T, class U>
size_t Helper(const D<T>& array, D2<U>& dp, size_t left, size_t right) {
  if (right - left < 3) {
    return 0;
  }
  U& el = dp[left][right];
  if (el.IsDefined()) {
    return el.Get();
  }
  for (size_t i = left + 1; i < right - 1; ++i) {
    size_t t1 = array[left] * array[i] * array[right - 1];
    size_t t2 = Helper(array, dp, left, i + 1) + Helper(array, dp, i, right);
    size_t t3 = t1 + t2;
    if (el.IsUndefined() || t3 < el.Get()) {
      el.Set(t3);
    }
  }
  return el.Get();
}

template <class T>
size_t Solution(const D<T>& array) {
  if (array.Size() < 3) {
    return 0;
  }
  using U = Optional<size_t>;
  size_t size = array.Size();
  D2<U> dp(size + 1, D<U>(size + 1, U()));
  Helper(array, dp, 0, size);
  return dp[0][size].Get();
}

using T = int64_t;

int main() {
  size_t n = 0;
  std::cin >> n;

  D<T> array(n);
  array.Input();

  std::cout << Solution(array);
}