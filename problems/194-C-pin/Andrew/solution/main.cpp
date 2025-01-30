// Copyright 2024 Andrew

#include <cstddef>
#include <optional>
#include <vector>
#include <algorithm>
#include <iostream>

class Ptr {
  using T = int;

 private:
  T index_;

 public:
  template <class U>
    requires requires(U i) {
      { i } -> std::convertible_to<T>;
    }
  explicit Ptr(U i) : index_(static_cast<T>(i)) {
  }
  Ptr() : index_(-1) {
  }
  Ptr(std::nullptr_t) : Ptr() {  // NOLINT
  }

  T Index() const {
    return index_;
  }

  bool operator==(std::nullptr_t) const {
    return index_ < 0;
  }
  bool operator!=(std::nullptr_t) const {
    return !(*this == nullptr);
  }
  operator bool() const {  // NOLINT
    return *this != nullptr;
  }

  operator T() const = delete;

  auto operator++() {
    return Ptr(++index_);
  }
  auto operator++(int) {
    return Ptr(index_++);
  }
  auto operator--() {
    return Ptr(--index_);
  }
  auto operator--(int) {
    return Ptr(index_--);
  }

  friend auto& operator<<(std::ostream& os, const Ptr& ptr) {  // NOLINT
    os << ptr.index_;
    return os;
  }
  bool operator==(Ptr other) const {
    return index_ == other.index_;
  }
  bool operator!=(Ptr other) const {
    return !(*this == other);
  }
};

template <class ValueType, class OperationType>
class SegmentTree {
  using PointerType = Ptr;

 protected:
  size_t Size() {
    return size_;
  }
  PointerType GetRoot() {
    return Check(0);
  }
  PointerType Check(int node) {
    if (node >= 0 && node < static_cast<int>(2 * Size() - 1)) {
      return PointerType(node);
    }
    return nullptr;
  }
  PointerType Parent(PointerType node) {
    if (node == GetRoot()) {
      return node;  // no parent
    }
    return Check((node.Index() - 1) / 2);
  }
  PointerType Left(PointerType node) {
    return Check(2 * node.Index() + 1);
  }
  PointerType Right(PointerType node) {
    return Check(Left(node).Index() + 1);
  }
  PointerType Leaf(size_t index) {
    return Check(index + Size() - 1);
  }
  PointerType Index(PointerType leaf) {
    return Check(leaf.Index() - Size() + 1);
  }
  ValueType& At(PointerType node) {
    return nodes_[node.Index()];
  }
  ValueType Result(PointerType lhs, PointerType rhs) {
    if (!lhs) {
      return At(rhs);
    }
    if (!rhs) {
      return At(lhs);
    }
    return operation_(At(lhs), At(rhs));
  }

 public:
  explicit SegmentTree(const std::vector<ValueType>& vec, const OperationType& operation)
      : size_(vec.size()), nodes_(2 * (size_ + 1)), operation_(operation) {
    if (Size() == 0) {
      throw std::runtime_error("Empty vector");
    }
    Build(vec);
  }

  void Build(const std::vector<ValueType>& vec) {
    for (size_t i = 0; i < Size(); ++i) {
      At(Leaf(i)) = vec[i];
    }
    for (int i = Leaf(0).Index() - 1; i >= 0; --i) {
      auto node = PointerType(i);
      if (Left(node) || Right(node)) {
        At(node) = Result(Left(node), Right(node));
      }
    }
  }

  ValueType Query(size_t left, size_t right) {
    std::optional<ValueType> lans;
    std::optional<ValueType> rans;
    auto l = Leaf(left);
    auto r = Leaf(right);
    while (l.Index() < r.Index()) {
      if (l != Left(Parent(l))) {
        lans = (lans ? operation_(lans.value(), At(l)) : At(l));
      }
      if (r != Right(Parent(r))) {
        rans = (rans ? operation_(rans.value(), At(r)) : At(r));
      }
      l = Parent(PointerType(l.Index() + 1));
      r = Parent(PointerType(r.Index() - 1));
    }
    if (l == r) {
      lans = (lans ? operation_(lans.value(), At(l)) : At(l));
    }
    if (!rans.has_value()) {
      return lans.value();
    }
    return operation_(lans.value(), rans.value());
  }

 protected:
  const size_t size_;
  std::vector<ValueType> nodes_;
  const OperationType operation_;
};

int main() {
  size_t n = 0;
  size_t k = 0;
  std::cin >> n >> k;
  std::vector<size_t> vec(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  auto min = [](size_t a, size_t b) { return std::min(a, b); };
  SegmentTree st(vec, min);

  for (size_t i = 0; i < k; ++i) {
    size_t l = 0;
    size_t r = 0;
    std::cin >> l >> r;
    std::cout << st.Query(l - 1, r - 1) << '\n';
  }
  return 0;
}
