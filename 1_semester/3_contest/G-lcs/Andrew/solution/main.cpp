#include <iostream>

template <class T>
T InputResult() {
  T value;
  std::cin >> value;
  return value;
}

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
auto LCSsizes(const DynArray<T>& first, const DynArray<T>& second) {
  DynArray<DynArray<T>> dp(first.Size() + 1, DynArray<T>(second.Size() + 1, T()));

  for (size_t i = 1; i <= first.Size(); ++i) {
    for (size_t j = 1; j <= second.Size(); ++j) {
      if (first[i - 1] == second[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
      }
    }
  }

  return dp;
}

template <class T>
auto LCS(const DynArray<T>& first, const DynArray<T>& second) {
  if (first.Size() == 0 || second.Size() == 0) {
    return DynArray<T>();
  }

  auto dp = LCSsizes<T>(first, second);

  size_t result_size = dp[first.Size()][second.Size()];
  DynArray<T> result(result_size, T());

  size_t fi = first.Size();
  size_t si = second.Size();
  size_t ri = result.Size();

  while (fi > 0 && si > 0) {
    if (first[fi - 1] == second[si - 1]) {
      result[--ri] = first[fi - 1];
      --fi;
      --si;
    } else if (dp[fi - 1][si] == dp[fi][si]) {
      --fi;
    } else {
      --si;
    }
  }

  return result;
}

template <class T>
void Solution(const DynArray<T>& first, const DynArray<T>& second) {
  LCS(first, second).Output();
}

using T = int64_t;

int main() {
  DynArray<T> first(InputResult<size_t>());
  first.Input();

  DynArray<T> second(InputResult<size_t>());
  second.Input();

  Solution(first, second);
}