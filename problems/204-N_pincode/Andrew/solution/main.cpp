// Copyright 2024 Andrew

#include <optional>
#include <vector>
#include <algorithm>
#include <iostream>

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

 protected:
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

  std::optional<ValueType> QueryHelper(PointerType node, const NodeDomain& query_domain,
                                       const NodeDomain& node_domain) {
    const auto [left, right] = query_domain;
    auto [l, r] = node_domain;
    if (r < left || l > right) {
      // [l, r] doesn't intersect [left, right]
      return {};
    }
    if (left <= l && r <= right) {
      // [l, r] subseteq [left, right]
      return At(node).value;
    }
    auto mid = (l + r) / 2;
    auto lhs = QueryHelper(Left(node), query_domain, {l, mid});
    auto rhs = QueryHelper(Right(node), query_domain, {mid + 1, r});
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

  auto Query(size_t left, size_t right) {
    if (left > right || right >= Size()) {
      throw std::runtime_error("Query: invalid range");
    }
    return QueryHelper(GetRoot(), {left, right}, RootDomain()).value();
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

template <class ValueType, class OperationType>
class SegmentTree2 {
 public:
  using ST = SegmentTree<ValueType, OperationType>;
  using Data = std::vector<ST>;
  using Matrix = std::vector<std::vector<ValueType>>;
  struct NodePoint {
    size_t x;
    size_t y;
  };
  using NodeDomain = std::pair<NodePoint, NodePoint>;

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

  SegmentTree2(size_t size_x, size_t size_y, const OperationType& operation)
      : size_x_(size_x), size_y_(size_y), operation_(operation), data_(size_x_, {size_y_, operation}) {
  }
  explicit SegmentTree2(size_t size_x, size_t size_y, const Matrix& matrix, const OperationType& operation)
      : SegmentTree2(size_x, size_y, operation) {
    Build(matrix);
  }

  void BuildY(size_t x, const Matrix& matrix) {
    data_[x].Build(matrix[x]);
  }

  void Build(const Matrix& matrix) {
    for (size_t x = 0; x < size_x_; ++x) {
      BuildY(x, matrix);
    }
  }

  std::optional<ValueType> QueryHelper(NodeDomain query_domain) {
    auto [p1, p2] = query_domain;
    if (p1.x > p2.x) {
      return {};
    }
    if (p1.x == p2.x) {
      return data_[p1.x].Query(p1.y, p2.y);
    }
    auto mid_x = (p1.x + p2.x) / 2;
    auto lhs = QueryHelper({p1, {mid_x, p2.y}});
    auto rhs = QueryHelper({{mid_x + 1, p1.y}, p2});
    return Operation(lhs, rhs);
  }

  ValueType Query(NodePoint first, NodePoint second) {
    return QueryHelper({first, second}).value();
  }

  size_t size_x_;
  size_t size_y_;
  const OperationType operation_;
  Data data_;
};

int main() {
  using T = int32_t;

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

  SegmentTree2 tree(size_x, size_y, matrix, min);

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
    std::cout << tree.Query({x1, y1}, {x2, y2}) << '\n';
  }
  return 0;
}
