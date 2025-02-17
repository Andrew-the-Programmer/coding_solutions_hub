// Copyright 2024 Andrew

#include <cstddef>
#include <iostream>
#include <memory>

template <class ValueType, class Priority, class OperationType>
  requires requires(const Priority& pr1, const Priority& pr2) {
    { pr1 < pr2 } -> std::same_as<bool>;
  } && requires(const OperationType op, const ValueType v1, const ValueType v2) {
    { op(v1, v2) } -> std::same_as<ValueType>;
  }
class Treap {
 public:
  struct Node : std::enable_shared_from_this<Node> {
   public:
    using PointerType = std::shared_ptr<Node>;

    ValueType value;
    Priority priority;
    size_t mass;
    ValueType op;

   protected:
    PointerType left = nullptr;
    PointerType right = nullptr;

   public:
    void Update() {
      mass = 1;
      if (left) {
        mass += left->mass;
      }
      if (right) {
        mass += right->mass;
      }
    }
    PointerType Left() {
      return left;
    }
    PointerType Right() {
      return right;
    }
    void SetLeft(PointerType left) {
      this->left = left;
      Update();
    }
    void SetRight(PointerType right) {
      this->right = right;
      Update();
    }
    template <class... Args>
    static PointerType New(Args&&... args) {
      return std::make_shared<Node>(std::forward<Args>(args)...);
    }
    Node(const ValueType& value, const Priority& priority) : value(value), priority(priority), mass(1), op(value) {
    }
  };

  using PointerType = typename Node::PointerType;

 protected:
  template <class... Args>
  static PointerType NewNode(Args&&... args) {
    return Node::New(std::forward<Args>(args)...);
  }

  ValueType Operation(const ValueType& lhs, const ValueType& rhs) {
    return operation_(lhs, rhs);
  }

  void Update(PointerType node) {
    auto val = node->value;
    if (node->Left()) {
      val = Operation(node->Left()->op, val);
    }
    if (node->Right()) {
      val = Operation(val, node->Right()->op);
    }
    node->op = val;
  }

  size_t Mass(PointerType node) const {
    if (!node) {
      return 0;
    }
    return node->mass;
  }

  std::pair<PointerType, PointerType> Split(PointerType node, size_t index) {
    if (!node) {
      return {nullptr, nullptr};
    }
    auto left_mass = Mass(node->Left());
    if (index <= left_mass) {
      auto [l, r] = Split(node->Left(), index);
      node->SetLeft(r);
      Update(node);
      return {l, node};
    }
    auto [l, r] = Split(node->Right(), index - left_mass - 1);
    node->SetRight(l);
    Update(node);
    return {node, r};
  }

  PointerType Merge(PointerType left, PointerType right) {
    if (!left) {
      return right;
    }
    if (!right) {
      return left;
    }
    if (left->priority < right->priority) {
      left->SetRight(Merge(left->Right(), right));
      Update(left);
      return left;
    }
    right->SetLeft(Merge(left, right->Left()));
    Update(right);
    return right;
  }

 public:
  explicit Treap(const OperationType& operation) : root_(nullptr), operation_(operation) {
  }

  void Insert(size_t index, ValueType value, Priority priority) {
    auto new_node = NewNode(value, priority);
    auto [l, r] = Split(root_, index);
    root_ = Merge(Merge(l, new_node), r);
  }

  auto Query(size_t left, size_t right) {
    auto [l1, r1] = Split(root_, right + 1);
    auto [l2, r2] = Split(l1, left);
    auto res = r2->op;
    root_ = Merge(Merge(l2, r2), r1);
    return res;
  }

 protected:
  PointerType root_;
  const OperationType operation_;
};

int main() {
  using ValueType = int64_t;
  using Priority = size_t;

  auto min = [](ValueType lhs, ValueType rhs) { return std::min(lhs, rhs); };

  Treap<ValueType, Priority, decltype(min)> treap(min);

  size_t n{};
  std::cin >> n;
  char request{};
  for (size_t i = 0; i < n; ++i) {
    std::cin >> request;
    switch (request) {
      case '+': {
        size_t index{};
        ValueType value{};
        std::cin >> index >> value;
        treap.Insert(index, value, std::rand());
        break;
      }
      case '?': {
        size_t l{};
        size_t r{};
        std::cin >> l >> r;
        --l;
        --r;
        std::cout << treap.Query(l, r) << '\n';
        break;
      }
    }
  }
  return 0;
}
