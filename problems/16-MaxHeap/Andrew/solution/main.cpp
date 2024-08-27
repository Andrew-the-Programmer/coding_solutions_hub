#include <iostream>

struct HeapIsEmpty {};
struct HeapIsFull {};
struct IndexIsOutOfRange {};
struct InvalidCommand {};
struct SomethingWentWrong {};

template <class T>
class DynArray {
 public:
  DynArray() : capacity_(0), size_(0), data_(nullptr) {
  }
  explicit DynArray(size_t capacity) : capacity_(capacity), size_(0), data_(new T[capacity]) {
  }
  DynArray(size_t size, const T& def_value) : capacity_(2 * size), size_(size), data_(new T[capacity_]) {
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

template <class T>
class MaxHeap : protected DynArray<T> {
 public:
  using Base = DynArray<T>;

 public:
  explicit MaxHeap(size_t max_size) : Base(max_size, T()) {
  }

  ~MaxHeap() = default;

 public:
  size_t MaxSize() const {
    return Base::Size();
  }

  size_t Size() const {
    return size_;
  }

  bool IsEmpty() const {
    return Size() == 0;
  }

  bool IsFull() const {
    return Size() >= MaxSize();
  }

 protected:
  void ThrowIfHeapIsFull() const {
    if (IsFull()) {
      throw HeapIsFull{};
    }
  }

  void ThrowIfHeapIsEmpty() const {
    if (IsEmpty()) {
      throw HeapIsEmpty{};
    }
  }

  bool IsInBounds(size_t index) const {
    return index < Size();
  }

  void ThrowIfOutOfRange(size_t index) const {
    if (!IsInBounds(index)) {
      throw IndexIsOutOfRange{};
    }
  }

 protected:
  void Increment() {
    ThrowIfHeapIsFull();
    ++size_;
  }

  void Decrement() {
    ThrowIfHeapIsEmpty();
    --size_;
  }

  static size_t Left(size_t index) {
    return 2 * index + 1;
  }

  static size_t Right(size_t index) {
    return 2 * index + 2;
  }

  static size_t Parent(size_t index) {
    if (index == 0) {
      return 0;  // no parent
    }
    return (index - 1) / 2;
  }

 protected:
  const T& RawAt(size_t index) const {
    return Base::At(index);
  }

  T& RawAt(size_t index) {
    return Base::At(index);
  }

 public:
  const T& At(size_t index) const {
    ThrowIfOutOfRange(index);
    return RawAt(index);
  }

  T& At(size_t index) {
    ThrowIfOutOfRange(index);
    return RawAt(index);
  }

  void Swap(size_t i, size_t j) {
    std::swap(At(i), At(j));
  }

  size_t MaxChild(size_t index) const {
    ThrowIfOutOfRange(index);

    size_t left = Left(index);
    size_t right = Right(index);

    if (!IsInBounds(left)) {
      return index;
    }
    if (IsInBounds(right) && At(right) > At(left)) {
      return right;
    }
    return left;
  }

  size_t SiftDown(size_t index) {
    ThrowIfOutOfRange(index);
    size_t max_child = MaxChild(index);
    if (At(max_child) > At(index)) {
      Swap(max_child, index);
      return SiftDown(max_child);
    }
    return index;
  }

  size_t SiftUp(size_t index) {
    ThrowIfOutOfRange(index);
    auto parent = Parent(index);
    if (At(parent) < At(index)) {
      Swap(index, parent);
      return SiftUp(parent);
    }
    return index;
  }

  size_t BackIndex() const {
    ThrowIfHeapIsEmpty();
    return Size() - 1;
  }

  void PushBack(const T& value) {
    Increment();
    At(BackIndex()) = value;
  }

  T& Back() {
    return At(BackIndex());
  }

 public:
  const T& Back() const {
    return At(BackIndex());
  }

  const T& Max() const {
    ThrowIfHeapIsEmpty();
    return At(0);
  }

 public:
  size_t Push(const T& value) {
    ThrowIfHeapIsFull();
    PushBack(value);
    return SiftUp(BackIndex());
  }

  std::pair<size_t, T> Pop(size_t index) {
    ThrowIfOutOfRange(index);

    if (index == BackIndex()) {
      Decrement();
      return {index + 1, RawAt(index)};
    }
    Swap(index, BackIndex());
    Decrement();
    std::pair<size_t, T> result = {SiftDown(index) + 1, RawAt(Size())};
    SiftUp(index);
    return result;
  }

  std::pair<size_t, T> PopMax() {
    ThrowIfHeapIsEmpty();

    if (Size() == 1) {
      Decrement();
      return {0, RawAt(0)};
    }
    return Pop(0);
  }

 public:
  void Log() const {
    for (size_t i = 0; i < Size(); ++i) {
      std::cout << At(i) << ' ';
    }
  }

 protected:
  size_t size_ = 0;
};

template <typename T, typename U>
std::ostream& operator<<(std::ostream& stream, const std::pair<T, U>& p) {
  stream << p.first << ' ' << p.second;
  return stream;
}

template <class T, class S = std::istream&>
T InputResult(S stream = std::cin) {
  T value;
  stream >> value;
  return value;
}

template <class T>
void Output(const T& value) {
  std::cout << value << std::endl;
}

void ErrorOutput() {
  Output(-1);
}

using T = int64_t;
using D = MaxHeap<T>;

int main() {
  size_t n = 0;
  size_t m = 0;

  int command = 0;

  std::cin >> n >> m;

  D deque(n);

  for (size_t i = 0; i < m; ++i) {
    std::cin >> command;

    try {
      switch (command) {
        case 1: {
          Output(deque.PopMax());
          break;
        }
        case 2: {
          if (deque.IsFull()) {
            ErrorOutput();
            InputResult<T>();
            break;
          }
          Output(deque.Push(InputResult<T>()) + 1);
          break;
        }
        case 3: {
          Output(deque.Pop(InputResult<size_t>() - 1).second);
          break;
        }
        default: {
          throw InvalidCommand{};
        }
      }
    } catch (...) {
      ErrorOutput();
    }
  }

  deque.Log();
}