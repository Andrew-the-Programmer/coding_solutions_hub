// Copyright 2024 Andrew

#include <optional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <limits>

using Int = uint32_t;

size_t Power2LowerBound(size_t n) {
  size_t result = 1;
  while (result < n) {
    result *= 2;
  }
  return result;
}

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
requires requires(const ValueType& v1, const ValueType& v2, const OperationType& op) {
  { op(v1, v2) } -> std::same_as<ValueType>;
}
class SegmentTree {
 public:
  struct PromiseType {
   public:
    using F = ValueType;

    explicit PromiseType(const F& func) : promise_(func) {
    }
    PromiseType() : PromiseType(std::numeric_limits<F>::denorm_min()){};

    auto operator*=(const PromiseType& other) {
      promise_ += other.promise_;
      return *this;
    }
    auto operator*(const PromiseType& other) const {
      auto copy = *this;
      copy *= other;
      return copy;
    }
    auto operator()(const ValueType& value) const {
      return promise_ + value;
    }

   public:
    F promise_;
  };
  class Node {
   public:
    ValueType value;
    PromiseType promise;

    ValueType PromisedValue() {
      return promise(value);
    }
  };

  using PointerType = Ptr;

 protected:
  size_t Size() {
    return size_;
  }
  size_t HeapSize() {
    return p2lb_ + Size() - 1;
  }
  std::pair<size_t, size_t> RootDomain() {
    return {0, p2lb_ - 1};
  }
  PointerType GetRoot() {
    return Check(0);
  }
  PointerType Check(int node) {
    if (node >= 0 && node < static_cast<int>(HeapSize())) {
      return PointerType(node);
    }
    return nullptr;
  }
  PointerType Check(PointerType node) {
    return Check(node.Index());
  }
  PointerType Parent(PointerType node) {
    if (node == GetRoot()) {
      return nullptr;
    }
    return Check((node.Index() - 1) / 2);
  }
  PointerType Left(PointerType node) {
    return Check(2 * node.Index() + 1);
  }
  PointerType Right(PointerType node) {
    return Check(2 * node.Index() + 2);
  }
  PointerType Leaf(size_t index) {
    return Check(index + p2lb_ - 1);
  }
  PointerType Index(PointerType leaf) {
    return Check(leaf.Index() + 1 - p2lb_);
  }
  Node& At(PointerType node) {
    return nodes_[node.Index()];
  }
  std::optional<ValueType> Value(PointerType node) {
    if (!Check(node)) {
      return {};
    }
    return At(node).value;
  }
  std::optional<ValueType> Operation(const std::optional<ValueType>& lhs, const std::optional<ValueType>& rhs) {
    if (!lhs && !rhs) {
      return {};
    }
    if (!lhs) {
      return rhs.value();
    }
    if (!rhs) {
      return lhs.value();
    }
    return operation_(lhs.value(), rhs.value());
  }
  std::optional<ValueType> Result(PointerType lhs, PointerType rhs) {
    return Operation(Value(lhs), Value(rhs));
  }

  void Push(PointerType node, std::pair<size_t, size_t> node_domain) {
    if (!Check(node)) {
      return;
    }
    auto p = At(node).promise;
    if (Left(node)) {
      At(Left(node)).promise *= p;
    }
    if (Right(node)) {
      At(Right(node)).promise *= p;
    }
    // xD
    auto [l, r] = node_domain;
    At(node).value += p.promise_ * (r - l + 1);
    At(node).promise = PromiseType();
  }

  std::optional<ValueType> QueryHelper(PointerType node, const std::pair<size_t, size_t>& query_domain,
                                       const std::pair<size_t, size_t>& node_domain) {
    const auto [left, right] = query_domain;
    auto [l, r] = node_domain;
    if (r < left || l > right) {
      // [l, r] doesn't intersect [left, right]
      return {};
    }
    Push(node, node_domain);
    if (left <= l && r <= right) {
      // [l, r] subseteq [left, right]
      return At(node).value;
    }
    auto mid = (l + r) / 2;
    auto lhs = QueryHelper(Left(node), query_domain, {l, mid});
    auto rhs = QueryHelper(Right(node), query_domain, {mid + 1, r});
    return Operation(lhs, rhs);
  }

  void UpdateRangeHelper(PointerType node, const std::pair<size_t, size_t>& query_domain,
                         const std::pair<size_t, size_t>& node_domain, const PromiseType& operand) {
    const auto [left, right] = query_domain;
    auto [l, r] = node_domain;
    Push(node, node_domain);
    if (r < left || l > right) {
      // [l, r] doesn't intersect [left, right]
      return;
    }
    if (left <= l && r <= right) {
      // [l, r] subseteq [left, right]
      At(node).promise *= operand;
      Push(node, node_domain);
      return;
    }
    // Push(node, node_domain);
    auto mid = (l + r) / 2;
    UpdateRangeHelper(Left(node), query_domain, {l, mid}, operand);
    UpdateRangeHelper(Right(node), query_domain, {mid + 1, r}, operand);
    // Push(Left(node), {l, mid});
    // Push(Right(node), {mid + 1, r});
    At(node).value = Result(Left(node), Right(node)).value();
  }

 public:
  SegmentTree(size_t size, const OperationType& operation)
      : size_(size), p2lb_(Power2LowerBound(size_)), nodes_(HeapSize()), operation_(operation) {
  }

  auto Query(size_t left, size_t right) {
    if (left > right || left >= Size() || right >= Size()) {
      throw std::runtime_error("Query: invalid range");
    }
    return QueryHelper(GetRoot(), {left, right}, RootDomain()).value();
  }

  template <class Operand>
  requires requires(Operand op) {
    // op(operation_(a, b)) = operation_(op(a), op(b))
    PromiseType(op);
  }
  void UpdateRange(size_t left, size_t right, const Operand& new_promise) {
    if (left > right || right >= Size()) {
      throw std::runtime_error("Update: invalid range");
    }
    UpdateRangeHelper(GetRoot(), {left, right}, RootDomain(), PromiseType(new_promise));
  }

 protected:
  const size_t size_;
  // power of 2 lower bound of size_ (like std::lower_bound)
  // 2^(k-1) < size_ <= 2^k
  // p2lb = 2^k
  const size_t p2lb_;
  std::vector<Node> nodes_;
  const OperationType operation_;
};

Int NextRand(Int a, Int b, Int& cur) {
  cur = cur * a + b;
  return cur >> 8;
}

int main() {
  size_t n{};
  size_t q{};
  std::cin >> n >> q;
  Int a = 0;
  Int b = 0;
  Int cur = 0;
  std::cin >> a >> b;
  auto sum_o = [](Int lhs, Int rhs) -> Int { return lhs + rhs; };
  SegmentTree<Int, decltype(sum_o)> st(1 << 24, sum_o);
  for (size_t i = 0; i < n; ++i) {
    auto add = NextRand(a, b, cur);
    auto l = NextRand(a, b, cur);
    auto r = NextRand(a, b, cur);
    // std::cout << l << ' ' << r << '\n';
    if (l > r) {
      std::swap(l, r);
    }
    st.UpdateRange(l, r, add);
  }
  Int sum = 0;
  for (size_t i = 0; i < q; ++i) {
    auto l = NextRand(a, b, cur);
    auto r = NextRand(a, b, cur);
    if (l > r) {
      std::swap(l, r);
    }
    auto q = st.Query(l, r);
    std::cout << q << '\n';
    sum += st.Query(l, r);
  }
  std::cout << sum << '\n';
  return 0;
}
