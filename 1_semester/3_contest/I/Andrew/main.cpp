#include <iostream>

template <class T>
auto Min(const T& value) {
  return value;
}

template <class T, class U, class... Tail>
auto Min(const T& t, const U& u, const Tail&... tail) {
  return Min((u < t ? u : t), tail...);
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
    T value = T();
    for (size_t i = Size(); i < Capacity(); ++i) {
      std::cin >> value;
      PushBack(value);
    }
  }

 protected:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T* data_ = nullptr;
};

template <class T>
size_t Solution(const DynArray<T>& s1, const DynArray<T>& s2) {
  DynArray<DynArray<size_t>> dp(s1.Size() + 1, DynArray<size_t>(s2.Size() + 1, T()));

  for (size_t i = 0; i <= s1.Size(); ++i) {
    for (size_t j = 0; j <= s2.Size(); ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = i + j;
      } else if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = 1 + Min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
      }
    }
  }

  // std::cout << '\n';
  // for (size_t i = 0; i <= s1.Size(); ++i) {
  //   dp[i].Output();
  //   std::cout << '\n';
  // }
  // std::cout << '\n';

  return dp[s1.Size()][s2.Size()];
}

template <class T>
void GetString(DynArray<T>& string) {
  char c = 0;
  while (true) {
    c = static_cast<char>(std::getchar());
    if (c == ' ' || c == '\n' || c == 0) {
      break;
    }
    string.PushBack(c);
  }
}

using C = char;
using String = DynArray<C>;

int main() {
  String s1(5001);
  String s2(5001);
  GetString(s1);
  GetString(s2);

  std::cout << Solution(s1, s2);
}