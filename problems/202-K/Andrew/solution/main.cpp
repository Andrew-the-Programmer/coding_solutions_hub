// Copyright 2024 Andrew

#include <cstddef>
#include <iostream>
#include <memory>

template <class Key, class Priority, class Cmp = std::less<Priority>>
  requires requires(const Cmp& cmp, const Priority& lhs, const Priority& rhs) {
    { cmp(lhs, rhs) } -> std::same_as<bool>;
  } && requires(const Key& key1, const Key& key2) {
    { key1 < key2 } -> std::same_as<bool>;
  }
class Treap {
 public:
  struct Node : std::enable_shared_from_this<Node> {
   public:
    using PointerType = std::shared_ptr<Node>;

    Key key;
    Priority priority;
    Key sum = 0;

   protected:
    PointerType left = nullptr;
    PointerType right = nullptr;

   public:
    PointerType Left() {
      return left;
    }
    PointerType Right() {
      return right;
    }

    void Update() {
      sum = key;
      if (left) {
        sum += left->sum;
      }
      if (right) {
        sum += right->sum;
      }
    }
    void SetLeft(PointerType left) {
      this->left = left;
      Update();
    }
    void SetRight(PointerType right) {
      this->right = right;
      Update();
    }
    void SetChild(PointerType child) {
      if (child->key < key) {
        SetLeft(child);
      } else {
        SetRight(child);
      }
    }
    PointerType Go(const Key& key) {
      if (this->key < key) {
        return Right();
      }
      return Left();
    }
    template <class... Args>
    static PointerType New(Args&&... args) {
      return std::make_shared<Node>(std::forward<Args>(args)...);
    }
    Node(const Key& key, const Priority& priority) : key(key), priority(priority), sum(key) {
    }
  };

  using PointerType = typename Node::PointerType;

 protected:
  template <class... Args>
  static PointerType NewNode(Args&&... args) {
    return Node::New(std::forward<Args>(args)...);
  }
  bool Compare(const Priority& lhs, const Priority& rhs) {
    return cmp_(lhs, rhs);
  }
  size_t Sum(PointerType node) const {
    if (!node) {
      return 0;
    }
    return node->sum;
  }
  std::pair<PointerType, PointerType> Split(PointerType node, Key key) {
    if (!node) {
      return {nullptr, nullptr};
    }
    if (key > node->key) {
      auto split = Split(node->Right(), key);
      node->SetRight(split.first);
      return {node, split.second};
    }
    auto split = Split(node->Left(), key);
    node->SetLeft(split.second);
    return {split.first, node};
  }
  PointerType Merge(PointerType left, PointerType right) {
    if (!left) {
      return right;
    }
    if (!right) {
      return left;
    }
    if (Compare(left->priority, right->priority)) {
      left->SetRight(Merge(left->Right(), right));
      return left;
    }
    right->SetLeft(Merge(left, right->Left()));
    return right;
  }

 public:
  explicit Treap(const Cmp& cmp = Cmp()) : root_(nullptr), cmp_(cmp) {
  }

  bool Contains(Key key) const {
    auto node = root_;
    if (!node) {
      return false;
    }
    while (node && node->key != key) {
      node = node->Go(key);
    }
    return static_cast<bool>(node);
  }

  void Insert(Key key, Priority priority) {
    if (Contains(key)) {
      return;
    }
    auto new_node = NewNode(key, priority);
    auto [l, r] = Split(root_, key);
    root_ = Merge(Merge(l, new_node), r);
  }

  auto QuerySum(Key left, Key right) {
    auto [l1, r1] = Split(root_, right + 1);
    auto [l2, r2] = Split(l1, left);
    auto res = Sum(r2);
    root_ = Merge(Merge(l2, r2), r1);
    return res;
  }

 protected:
  PointerType root_;
  const Cmp cmp_;
};

int main() {
  using Key = size_t;
  using Priority = size_t;

  Treap<Key, Priority, std::less<Priority>> treap;

  size_t n{};
  std::cin >> n;
  char request{};
  for (size_t i = 0; i < n; ++i) {
    std::cin >> request;
    switch (request) {
      case '+': {
        Key key{};
        std::cin >> key;
        treap.Insert(key, std::rand());
        break;
      }
      case '?': {
        Key l{};
        Key r{};
        std::cin >> l >> r;
        std::cout << treap.QuerySum(l, r) << '\n';
        break;
      }
    }
  }
  return 0;
}
