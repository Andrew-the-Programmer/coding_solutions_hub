// Copyright 2024 Andrew

// try number 6

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

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
    using LinkType = std::weak_ptr<Node>;

    Key key;
    Priority priority;
    size_t mass = 0;

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
      mass = 1;
      if (left) {
        mass += left->mass;
      }
      if (right) {
        mass += right->mass;
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
    Node(const Key& key, const Priority& priority) : key(key), priority(priority) {
    }
  };

  using PointerType = typename Node::PointerType;
  using LinkType = typename Node::LinkType;

 protected:
  template <class... Args>
  static PointerType NewNode(Args&&... args) {
    return Node::New(std::forward<Args>(args)...);
  }
  bool Compare(const Priority& lhs, const Priority& rhs) {
    return cmp_(lhs, rhs);
  }
  size_t Mass(PointerType node) const {
    if (!node) {
      return 0;
    }
    return node->mass;
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

  void Insert(Key key, Priority priority) {
    if (Contains(key)) {
      return;
    }
    auto new_node = NewNode(key, priority);
    if (!root_) {
      root_ = new_node;
      return;
    }
    PointerType parent = nullptr;
    auto node = root_;
    while (node && !Compare(priority, node->priority)) {
      parent = node;
      node->mass++;
      node = node->Go(key);
    }
    if (!node) {
      parent->SetChild(new_node);
      return;
    }
    // priority < node->priority
    auto split = Split(node, key);
    new_node->SetLeft(split.first);
    new_node->SetRight(split.second);
    if (!parent) {
      root_ = new_node;
      return;
    }
    parent->SetChild(new_node);
  }

  void Delete(Key key) {
    if (!Contains(key)) {
      return;
    }
    auto node = root_;
    PointerType parent = nullptr;
    while (node && node->key != key) {
      parent = node;
      node->mass--;
      node = node->Go(key);
    }
    if (!node) {
      return;
    }
    auto merge = Merge(node->Left(), node->Right());
    if (!parent) {
      root_ = merge;
      return;
    }
    if (parent->key > key) {
      parent->SetLeft(merge);
    } else {
      parent->SetRight(merge);
    }
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

  PointerType Next(Key key) const {
    auto node = root_;
    if (!node) {
      return nullptr;
    }
    while (key >= node->key && node->Right()) {
      node = node->Right();
    }
    while (node->Left() && node->Left()->key >= key) {
      node = node->Left();
    }
    if (key > node->key) {
      return nullptr;
    }
    return node;
  }

  PointerType Prev(Key key) const {
    auto node = root_;
    if (!node) {
      return nullptr;
    }
    while (key <= node->key && node->Left()) {
      node = node->Left();
    }
    while (node->Right() && node->Right()->key <= key) {
      node = node->Right();
    }
    if (key < node->key) {
      return nullptr;
    }
    return node;
  }

  PointerType Kth(size_t k) const {
    auto node = root_;
    while (node) {
      auto left_mass = Mass(node->Left());
      if (k == left_mass) {
        return node;
      }
      if (k < left_mass) {
        node = node->Left();
      } else {
        k -= (left_mass + 1);
        node = node->Right();
      }
    }
    return nullptr;
  }

 protected:
  PointerType root_;
  const Cmp cmp_;
};

int main() {
  using Key = size_t;
  using Priority = size_t;

  std::srand(time(nullptr));

  Treap<Key, Priority, std::less<Priority>> treap;

  std::string request{};
  while (std::cin >> request) {
    if (request == "insert") {
      Key key{};
      std::cin >> key;
      treap.Insert(key, std::rand() % 3);
      continue;
    }
    if (request == "delete") {
      Key key{};
      std::cin >> key;
      treap.Delete(key);
      continue;
    }
    if (request == "exists") {
      Key key{};
      std::cin >> key;
      std::cout << (treap.Contains(key) ? "true" : "false") << '\n';
      continue;
    }
    if (request == "next") {
      Key key{};
      std::cin >> key;
      auto next = treap.Next(key);
      std::cout << (next ? std::to_string(next->key) : "none") << '\n';
      continue;
    }
    if (request == "prev") {
      Key key{};
      std::cin >> key;
      auto prev = treap.Prev(key);
      std::cout << (prev ? std::to_string(prev->key) : "none") << '\n';
      continue;
    }
    if (request == "kth") {
      size_t k{};
      std::cin >> k;
      auto kth = treap.Kth(k);
      std::cout << (kth ? std::to_string(kth->key) : "none") << '\n';
      continue;
    }
  }
  return 0;
}
