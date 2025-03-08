// Copyright 2024 Andrew

#include <concepts>
#include <iostream>
#include <vector>
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
    using PointerType = std::shared_ptr<Node>;
    using LinkType = std::weak_ptr<Node>;

    Key key;
    Priority priority;
    size_t word_id;
    PointerType left = nullptr;
    PointerType right = nullptr;
    LinkType parent = PointerType(nullptr);

    PointerType Left() {
      return left;
    }
    PointerType Right() {
      return right;
    }
    PointerType Parent() {
      return parent.lock();
    }

    void Update() {
      if (left) {
        left->parent = this->shared_from_this();
      }
      if (right) {
        right->parent = this->shared_from_this();
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

    template <class... Args>
    static PointerType New(Args&&... args) {
      return std::make_shared<Node>(std::forward<Args>(args)...);
    }

    Node(const Key& key, const Priority& priority, size_t word_num) : key(key), priority(priority), word_id(word_num) {
    }
  };

  using PointerType = typename Node::PointerType;
  using LinkType = typename Node::LinkType;

 protected:
  template <class... Args>
  static PointerType NewNode(Args&&... args) {
    return Node::New(std::forward<Args>(args)...);
  }

  template <class Op>
    requires requires(PointerType node, const Op& func) {
      { func(node) } -> std::same_as<void>;
    }
  void InOrderTraverseHelper(PointerType node, const Op& func) {
    if (!node) {
      return;
    }
    InOrderTraverseHelper(node->Left(), func);
    func(node);
    InOrderTraverseHelper(node->Right(), func);
  }

  bool Compare(const Priority& lhs, const Priority& rhs) {
    return cmp_(lhs, rhs);
  }

 public:
  explicit Treap(const std::vector<std::pair<Key, Priority>>& nodes, const Cmp& cmp = Cmp())
      : root_(nullptr), cmp_(cmp) {
    Build(nodes);
  }

  void Build(const std::vector<std::pair<Key, Priority>>& nodes) {
    // keys are sorted
    PointerType last = nullptr;
    size_t word_counter = 0;
    // kv = kiwi
    for (const auto& kv : nodes) {
      auto new_node = NewNode(kv.first, kv.second, word_counter++);
      auto node = last;
      while (node && Compare(new_node->priority, node->priority)) {
        node = node->Parent();
      }
      if (!node) {
        new_node->SetLeft(root_);
        root_ = new_node;
      } else {
        new_node->SetLeft(node->Right());
        node->SetRight(new_node);
      }
      last = new_node;
    }
  }

  void Solution() {
    std::cout << "YES\n";
    InOrderTraverseHelper(root_, [](const PointerType& node) {
      std::cout << (node->Parent() ? node->Parent()->word_id + 1 : 0) << ' ';
      std::cout << (node->Left() ? node->Left()->word_id + 1 : 0) << ' ';
      std::cout << (node->Right() ? node->Right()->word_id + 1 : 0) << '\n';
    });
  }

 protected:
  PointerType root_;
  const Cmp cmp_;
};

int main() {
  using Key = int;
  using Priority = int;

  size_t n{};
  std::cin >> n;
  std::vector<std::pair<Key, Priority>> nodes(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> nodes[i].first >> nodes[i].second;
  }
  Treap treap(nodes);
  treap.Solution();
  return 0;
}
