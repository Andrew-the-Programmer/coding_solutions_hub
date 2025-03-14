#include <iostream>

template <class T>
struct TreeNode {
  using Node = TreeNode;
  using NodePtr = Node*;
  using ConstNodePtr = const Node*;

  explicit TreeNode(const T& key = T(), NodePtr parent = nullptr, NodePtr left = nullptr, NodePtr right = nullptr)
      : value(key), left(left), right(right), parent(parent) {
  }

  NodePtr Push(const T& value) {
    if (value > this->value && right == nullptr) {
      return right = new Node(value, this);
    }
    if (value < this->value && left == nullptr) {
      return left = new Node(value, this);
    }
    return nullptr;
  }

  ConstNodePtr Max() const {
    if (right) {
      return right->Max();
    }
    return this;
  }

  ConstNodePtr Prev() const {
    if (left) {
      return left->Max();
    }
    return parent;
  }

 public:
  T value = T();
  NodePtr left = nullptr;
  NodePtr right = nullptr;
  NodePtr parent = nullptr;
};

template <class T>
class BinaryTree {
 public:
  using Node = TreeNode<T>;
  using NodePtr = Node*;
  using ConstNodePtr = const Node*;

  ~BinaryTree() {
    Clear(root_);
  }

  void Clear(NodePtr start) {
    if (!start) {
      return;
    }
    Clear(start->left);
    Clear(start->right);
    delete start;
  }

  void Insert(NodePtr node, const T& value) {
    if (!node) {
      return;
    }
    if (value > node->value) {
      if (node->right) {
        Insert(node->right, value);
      } else {
        node->Push(value);
      }
    } else if (value < node->value) {
      if (node->left) {
        Insert(node->left, value);
      } else {
        node->Push(value);
      }
    }
  }

  void Insert(const T& value) {
    if (!root_) {
      root_ = new Node(value);
    } else {
      Insert(root_, value);
    }
  }

  const T& SecondMax() const {
    return root_->Max()->Prev()->value;
  }

 protected:
  NodePtr root_ = nullptr;
};

template <class T, class S = std::istream&>
T InputResult(S stream = std::cin) {
  T value;
  stream >> value;
  return value;
}

using T = int64_t;
using Tree = BinaryTree<T>;

int main() {
  Tree tree;

  for (T value = InputResult<T>(); value != 0; std::cin >> value) {
    tree.Insert(value);
  }

  std::cout << tree.SecondMax();
}