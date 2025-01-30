// Copyright 2024 Andrew

#include <concepts>
#include <cstddef>
#include <optional>
#include <vector>
#include <iostream>
#include <limits>
// #include <boost/format.hpp>

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

   protected:
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
  void Update(PointerType node) {
    if (node && (Left(node) || Right(node))) {
      At(node).value = Result(Left(node), Right(node)).value();
    }
  }

 public:
  explicit SegmentTree(const std::vector<ValueType>& vec, const OperationType& operation)
      : size_(vec.size()), p2lb_(Power2LowerBound(size_)), nodes_(HeapSize()), operation_(operation) {
    if (Size() == 0) {
      throw std::runtime_error("Empty vector");
    }
    Build(vec);
  }

  void Build(const std::vector<ValueType>& vec) {
    // boost::format fmt("QueryHelper: node = %1%, value = %2%");
    for (size_t i = 0; i < Size(); ++i) {
      auto node = Leaf(i);
      At(node).value = vec[i];
      // std::cout << fmt % node % At(node).value << '\n';
    }
    for (auto i = Leaf(0).Index() - 1; i >= 0; --i) {
      auto node = PointerType(i);
      Update(node);
      // std::cout << fmt % node % At(node).value << '\n';
    }
  }

  void Push(PointerType node) {
    // boost::format fmt("Push: node = %1%, value = %2%");
    if (!Check(node)) {
      return;
    }
    // std::cout << fmt % node % At(node).value << std::endl;
    auto p = At(node).promise;
    if (Left(node)) {
      At(Left(node)).promise *= p;
    }
    if (Right(node)) {
      At(Right(node)).promise *= p;
    }
    At(node).value = p(At(node).value);
    At(node).promise = PromiseType();
  }

  std::optional<ValueType> QueryHelper(PointerType node, const std::pair<size_t, size_t>& query_domain,
                                       const std::pair<size_t, size_t>& node_domain) {
    const auto [left, right] = query_domain;
    auto [l, r] = node_domain;
    // boost::format fmt("QueryHelper: node = %1%, (l,r) = (%2%, %3%)");
    // std::cout << fmt % node % l % r << std::endl;
    if (r < left || l > right) {
      // [l, r] doesn't intersect [left, right]
      return {};
    }
    if (left <= l && r <= right) {
      // [l, r] subseteq [left, right]
      return At(node).PromisedValue();
    }
    Push(node);
    auto mid = (l + r) / 2;
    auto lhs = QueryHelper(Left(node), query_domain, {l, mid});
    auto rhs = QueryHelper(Right(node), query_domain, {mid + 1, r});
    // boost::format fmt2("QueryHelper: node = %1%, (lhs,rhs) = (%2%, %3%)");
    // std::cout << fmt2 % node % Str(lhs) % Str(rhs) << std::endl;
    return Operation(lhs, rhs);
  }

  auto Query(size_t left, size_t right) {
    if (left > right || left >= Size() || right >= Size()) {
      throw std::runtime_error("Query: invalid range");
    }
    return QueryHelper(GetRoot(), {left, right}, RootDomain()).value();
  }

  void UpdateRangeHelper(PointerType node, const std::pair<size_t, size_t>& query_domain,
                         const std::pair<size_t, size_t>& node_domain, const PromiseType& operand) {
    const auto [left, right] = query_domain;
    auto [l, r] = node_domain;
    // boost::format fmt("UpdateRange: node = %1%, (l,r) = (%2%, %3%)");
    // std::cout << fmt % node % l % r << std::endl;
    if (r < left || l > right) {
      // [l, r] doesn't intersect [left, right]
      return;
    }
    if (left <= l && r <= right) {
      // [l, r] subseteq [left, right]
      At(node).promise *= operand;
      return;
    }
    Push(node);
    auto mid = (l + r) / 2;
    UpdateRangeHelper(Left(node), query_domain, {l, mid}, operand);
    UpdateRangeHelper(Right(node), query_domain, {mid + 1, r}, operand);
    auto lhs = QueryHelper(Left(node), query_domain, {l, mid});
    auto rhs = QueryHelper(Right(node), query_domain, {mid + 1, r});
    At(node).value = Operation(lhs, rhs).value();
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

int main() {
  using T = int;
  size_t n{};
  std::cin >> n;
  std::vector<T> data(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> data[i];
  }
  auto max = [](T lhs, T rhs) -> T { return std::max(lhs, rhs); };
  SegmentTree st(data, max);

  // std::cout << sizeof(decltype(st)::Node) << std::endl;
  // return 0;

  size_t k = 0;
  std::cin >> k;

  for (size_t i = 0; i < k; ++i) {
    char request{};
    size_t l{};
    size_t r{};
    std::cin >> request >> l >> r;
    --l;
    --r;
    switch (request) {
      case 'a': {
        T value{};
        std::cin >> value;
        // auto add = [value = value](T v) -> T { return v + value; };
        st.UpdateRange(l, r, value);
        break;
      }
      case 'm': {
        std::cout << st.Query(l, r) << '\n';
        break;
      }
    }
  }
  return 0;
}
