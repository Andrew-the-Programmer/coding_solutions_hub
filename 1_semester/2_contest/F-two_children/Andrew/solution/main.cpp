#include <iostream>

template <class T>
struct TreeNode {
  using Node = TreeNode;
  using NodePtr = Node*;
  using ConstNodePtr = const Node*;

  explicit TreeNode(const T& key = T(), NodePtr left = nullptr, NodePtr right = nullptr)
      : value(key), left(left), right(right) {
  }

  NodePtr Push(const T& value) {
    if (value > this->value && right == nullptr) {
      return right = new Node(value);
    }
    if (value < this->value && left == nullptr) {
      return left = new Node(value);
    }
    return nullptr;
  }

  template <class Func = void(ConstNodePtr)>
  void Traverse(const Func& func = Func()) const {
    if (left) {
      left->Traverse(func);
    }
    func(this);
    if (right) {
      right->Traverse(func);
    }
  }

  bool HasTwoChildren() const {
    return left && right;
  }

 public:
  T value = T();
  NodePtr left = nullptr;
  NodePtr right = nullptr;
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
    }
    Insert(root_, value);
  }

  void OutputNodesWithTwoChildren() const {
    if (root_) {
      auto func = [](ConstNodePtr node) {
        if (node && node->HasTwoChildren()) {
          std::cout << node->value << '\n';
        }
      };
      root_->Traverse(func);
    }
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

  tree.OutputNodesWithTwoChildren();
}