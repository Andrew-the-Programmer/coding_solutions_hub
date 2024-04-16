#include <iostream>

template <class T>
struct TreeNode {
  using Node = TreeNode;
  using NodePtr = Node*;
  using ConstNodePtr = const Node*;

  explicit TreeNode(const T& key = T(), NodePtr parent = nullptr, NodePtr left = nullptr, NodePtr right = nullptr)
      : value(key), parent(parent), left(left), right(right) {
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

  template <class Func = void(ConstNodePtr)>
  void InorderTraversal(Func func = Func()) const {
    if (left) {
      left->InorderTraversal(func);
    }
    func(this);
    if (right) {
      right->InorderTraversal(func);
    }
  }

  template <class Func = void(ConstNodePtr)>
  void PostorderTraversal(Func func = Func()) const {
    if (left) {
      left->PostorderTraversal(func);
    }
    if (right) {
      right->PostorderTraversal(func);
    }
    func(this);
  }

 public:
  T value = T();
  NodePtr parent = nullptr;
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
    Clear();
  }

  void Clear(NodePtr start) {
    if (!start) {
      return;
    }
    Clear(start->left);
    Clear(start->right);
    delete start;
  }

  void Clear() {
    Clear(root_);
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

  void PreorderInsert(size_t size) {
    T value = T();
    NodePtr cur = nullptr;
    NodePtr max = nullptr;
    NodePtr local_max = nullptr;
    for (size_t i = 0; i < size; ++i) {
      std::cin >> value;
      if (i == 0) {
        Insert(value);
        max = cur = local_max = root_;
        std::cout << "value = " << value << ": ";
        InorderOutput();
        std::cout << std::endl;
        continue;
      }
      if (value < cur->value) {
        local_max = cur;
      } else if (value > cur->value && value > local_max->value) {
        NodePtr parent = nullptr;
        while (true) {
          parent = cur->parent;
          if (!parent || parent->value < cur->value || parent->value > value) {
            break;
          }
          cur = cur->parent;
        }
        local_max = cur->parent;
      } else if (value == cur->value) {
        throw std::logic_error("tree is not supposed to have multiple identical values");
      }
      cur = cur->Push(value);
      std::cout << "value = " << value << ": ";
      InorderOutput();
      std::cout << std::endl;
    }
  }

  void PostorderOutput() const {
    if (!root_) {
      return;
    }
    auto func = [](ConstNodePtr node) { std::cout << node->value << ' '; };
    root_->PostorderTraversal(func);
  }

  void InorderOutput() const {
    if (!root_) {
      return;
    }
    auto func = [](ConstNodePtr node) { std::cout << node->value << ' '; };
    root_->InorderTraversal(func);
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

  size_t n = 0;
  std::cin >> n;

  tree.PreorderInsert(n);

  // tree.PostorderOutput();

  tree.InorderOutput();
}