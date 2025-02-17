// Copyright 2024 Andrew
// try number 2

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>
#include <string>

template <class KeyType, class PriorityType>
  requires requires(const PriorityType& pr1, const PriorityType& pr2) {
    { pr1 < pr2 } -> std::same_as<bool>;
  } && requires(const KeyType& key1, const KeyType& key2) {
    { key1 < key2 } -> std::same_as<bool>;
  }
class Treap {
 public:
  struct Node : std::enable_shared_from_this<Node> {
   public:
    using PointerType = std::shared_ptr<Node>;

   protected:
    KeyType key;
    PriorityType priority;
    size_t mass = 1;
    PointerType left = nullptr;
    PointerType right = nullptr;

   public:
    auto Left() {
      return left;
    }
    auto Right() {
      return right;
    }
    auto Mass() {
      return mass;
    }
    auto Key() {
      return key;
    }
    auto Priority() {
      return priority;
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
      if (child->Key() < key) {
        SetLeft(child);
      } else {
        SetRight(child);
      }
    }

    PointerType Go(const KeyType& key) {
      if (this->Key() < key) {
        return Right();
      }
      return Left();
    }

    template <class... Args>
    static PointerType New(Args&&... args) {
      return std::make_shared<Node>(std::forward<Args>(args)...);
    }
    Node(const KeyType& key, const PriorityType& priority) : key(key), priority(priority) {
    }
  };

  using PointerType = typename Node::PointerType;

 protected:
  template <class... Args>
  static PointerType NewNode(Args&&... args) {
    return Node::New(std::forward<Args>(args)...);
  }

  size_t Mass(PointerType node) const {
    if (!node) {
      return 0;
    }
    return node->Mass();
  }

  std::pair<PointerType, PointerType> Split(PointerType node, KeyType key) {
    if (!node) {
      return {nullptr, nullptr};
    }
    if (key > node->Key()) {
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
    if (left->Priority() < right->Priority()) {
      left->SetRight(Merge(left->Right(), right));
      return left;
    }
    right->SetLeft(Merge(left, right->Left()));
    return right;
  }

 public:
  explicit Treap() : root_(nullptr) {
  }

  void Insert(KeyType key, PriorityType priority) {
    if (Contains(key)) {
      return;
    }
    auto new_node = NewNode(key, priority);
    auto [left, right] = Split(root_, key);
    root_ = Merge(Merge(left, new_node), right);
  }

  void Delete(KeyType key) {
    if (!Contains(key)) {
      return;
    }
    auto [l, tr] = Split(root_, key);
    auto [m, r] = Split(tr, key + 1);
    root_ = Merge(l, r);
  }

  bool Contains(KeyType key) const {
    auto node = root_;
    if (!node) {
      return false;
    }
    while (node && node->Key() != key) {
      node = node->Go(key);
    }
    return node != nullptr;
  }

  PointerType Next(KeyType key) const {
    auto node = root_;
    if (!node) {
      return nullptr;
    }
    while (key >= node->Key() && node->Right()) {
      node = node->Right();
    }
    while (node->Left() && node->Left()->Key() >= key) {
      node = node->Left();
    }
    if (key > node->Key()) {
      return nullptr;
    }
    return node;
  }

  PointerType Prev(KeyType key) const {
    auto node = root_;
    if (!node) {
      return nullptr;
    }
    while (key <= node->Key() && node->Left()) {
      node = node->Left();
    }
    while (node->Right() && node->Right()->Key() <= key) {
      node = node->Right();
    }
    if (key < node->Key()) {
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
};

int main() {
  using RNG = std::mt19937;
  using KeyType = int64_t;
  using PriorityType = RNG::result_type;

  Treap<KeyType, PriorityType> treap;

  std::random_device dev;
  RNG rng(dev());
  std::uniform_int_distribution<PriorityType> rand_int;

  std::string request{};
  while (std::cin >> request) {
    if (request == "insert") {
      KeyType key{};
      std::cin >> key;
      treap.Insert(key, rand_int(rng));
      continue;
    }
    if (request == "delete") {
      KeyType key{};
      std::cin >> key;
      treap.Delete(key);
      continue;
    }
    if (request == "exists") {
      KeyType key{};
      std::cin >> key;
      std::cout << (treap.Contains(key) ? "true" : "false") << '\n';
      continue;
    }
    if (request == "next") {
      KeyType key{};
      std::cin >> key;
      auto next = treap.Next(key);
      std::cout << (next ? std::to_string(next->Key()) : "none") << '\n';
      continue;
    }
    if (request == "prev") {
      KeyType key{};
      std::cin >> key;
      auto prev = treap.Prev(key);
      std::cout << (prev ? std::to_string(prev->Key()) : "none") << '\n';
      continue;
    }
    if (request == "kth") {
      size_t k{};
      std::cin >> k;
      auto kth = treap.Kth(k);
      std::cout << (kth ? std::to_string(kth->Key()) : "none") << '\n';
      continue;
    }
  }
  return 0;
}
