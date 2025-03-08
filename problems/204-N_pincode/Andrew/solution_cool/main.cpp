// Copyright 2024 Andrew

#include <optional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>

namespace tuple {
// NOLINTBEGIN
template <typename Tuple, size_t... xs>
constexpr auto sub_tuple(const Tuple& t, std::index_sequence<xs...>) {
  return std::make_tuple(std::get<xs>(t)...);
}

template <typename Tuple, size_t x, size_t... xs>
constexpr auto sub_tail_tuple(const Tuple& t, std::index_sequence<x, xs...>) {
  return std::make_tuple(std::get<xs>(t)...);
}

template <typename Tuple>
constexpr auto tuple_head(const Tuple& t) {
  return std::get<0>(t);
}

template <typename Tuple>
constexpr auto tuple_last(const Tuple& t) {
  return std::get<std::tuple_size<Tuple>::value - 1>(t);
}

template <typename Tuple>
constexpr auto tuple_init(const Tuple& t) {
  constexpr size_t tuple_size = std::tuple_size<Tuple>::value;
  return sub_tuple(t, std::make_index_sequence<tuple_size - 1>());
}

template <typename Tuple>
constexpr auto tuple_tail(const Tuple& t) {
  constexpr size_t tuple_size = std::tuple_size<Tuple>::value;
  return sub_tail_tuple(t, std::make_index_sequence<tuple_size>());
}
// NOLINTEND
}  // namespace tuple

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
  struct Node {
    using Point = size_t;
    using Domain = std::pair<Point, Point>;
    ValueType value;
  };

 public:
  using NodePoint = Node::Point;
  using NodeDomain = Node::Domain;

 public:
  using PointerType = Ptr;

  size_t Size() {
    return size_;
  }
  size_t HeapSize() {
    return p2lb_ + Size() - 1;
  }
  NodeDomain RootDomain() {
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
  std::optional<ValueType> Value(PointerType node) {
    if (!Check(node)) {
      return {};
    }
    return At(node).value;
  }
  std::optional<ValueType> Result(PointerType lhs, PointerType rhs) {
    return Operation(Value(lhs), Value(rhs));
  }
  void Update(PointerType node) {
    if (node && (Left(node) || Right(node))) {
      At(node).value = Result(Left(node), Right(node)).value();
    }
  }

  template <class... Args>
  std::optional<ValueType> QueryHelper(PointerType node, const std::tuple<NodeDomain, Args...>& query,
                                       const NodeDomain& node_domain, std::tuple<Args...> tpl) {
    NodeDomain node_d = tuple::tuple_head(query);
    auto query_tail = tuple::tuple_tail(query);
    const auto [left, right] = node_d;
    auto [l, r] = node_domain;
    if (r < left || l > right) {
      // [l, r] doesn't intersect [left, right]
      return {};
    }
    if (left <= l && r <= right) {
      // [l, r] subseteq [left, right]
      return At(node).value.Query(query_tail);
    }
    auto mid = (l + r) / 2;
    auto lhs = QueryHelper(Left(node), query_d, {l, mid});
    auto rhs = QueryHelper(Right(node), query_d, {mid + 1, r});
    return Operation(lhs, rhs);
  }

 public:
  void Build(const std::vector<ValueType>& vec) {
    for (size_t i = 0; i < Size(); ++i) {
      auto node = Leaf(i);
      At(node).value = vec[i];
    }
    for (auto i = Leaf(0).Index() - 1; i >= 0; --i) {
      auto node = PointerType(i);
      Update(node);
    }
  }

  SegmentTree(size_t size, const OperationType& operation)
      : size_(size), p2lb_(Power2LowerBound(size_)), nodes_(HeapSize()), operation_(operation) {
  }
  SegmentTree(const std::vector<ValueType>& vec, const OperationType& operation) : SegmentTree(vec.size(), operation) {
    if (Size() == 0) {
      throw std::runtime_error("Empty vector");
    }
    Build(vec);
  }

  template <class... Args>
  auto Query(const std::tuple<NodeDomain, Args...>& query) {
    return QueryHelper(GetRoot(), query, RootDomain()).value();
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
  using T = int32_t;
  using NodeDomain = SegmentTree::NodeDomain;

  size_t size_x{};
  size_t size_y{};
  std::cin >> size_x >> size_y;
  std::vector<std::vector<T>> matrix(size_x, std::vector<T>(size_y));
  for (size_t x = 0; x < size_x; ++x) {
    for (size_t y = 0; y < size_y; ++y) {
      std::cin >> matrix[x][y];
    }
  }

  auto min = [](T lhs, T rhs) -> T { return std::min(lhs, rhs); };

  std::vector<SegmentTree<T, decltype(min)>> segment_trees(size_x, {size_y, min});

  using ST = SegmentTree<T, decltype(min)>;

  auto min_st = [](const ST& lhs, const ST& rhs) -> ST {
    auto size_lhs = lhs.HeapSize();
    auto size_rhs = rhs.HeapSize();
    for (size)
  };

  SegmentTree tree(segment_trees, min);

  size_t q{};
  std::cin >> q;
  for (size_t i = 0; i < q; ++i) {
    size_t x1{};
    size_t y1{};
    size_t x2{};
    size_t y2{};
    std::cin >> x1 >> y1 >> x2 >> y2;
    --x1;
    --y1;
    --x2;
    --y2;
    std::cout << tree.Query<std::pair<size_t, size_t>>({{x1, x2}, {y1, y2}}) << '\n';
  }
  return 0;
}
