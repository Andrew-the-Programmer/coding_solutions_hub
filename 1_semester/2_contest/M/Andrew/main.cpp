#include <iostream>

struct AvlTreeIsEmpty {};

template <class T>
struct AvlTreeNode {
  using Node = AvlTreeNode;
  using NodePtr = Node*;
  using ConstNodePtr = const Node*;
  using CRef = const T&;

  explicit AvlTreeNode(CRef value = T()) : value(value), height(1) {
  }

  void SetParent(NodePtr parent) {
    this->parent = parent;
  }

  void KeepParent() {
    if (left) {
      left->SetParent(this);
    }
    if (right) {
      right->SetParent(this);
    }
  }

  void SetRightChild(NodePtr child) {
    right = child;
    if (child) {
      child->parent = this;
    }
  }

  void SetLeftChild(NodePtr child) {
    left = child;
    if (child) {
      child->parent = this;
    }
  }

  void ReplaceChild(NodePtr old_child, NodePtr new_child) {
    if (left == old_child) {
      SetLeftChild(new_child);
    } else if (right == old_child) {
      SetRightChild(new_child);
    }
  }

  static void Split(NodePtr parent, NodePtr child) {
    if (!parent || !child) {
      return;
    }
    if (child == parent->left) {
      child->SetParent(nullptr);
      parent->SetLeftChild(nullptr);
    } else if (child == parent->right) {
      child->SetParent(nullptr);
      parent->SetRightChild(nullptr);
    }
  }

  size_t LeftHeight() const {
    return (left ? left->height : 0);
  }

  size_t RightHeight() const {
    return (right ? right->height : 0);
  }

  int BalanceFactor() const {
    return RightHeight() - LeftHeight();
  }

  void FixHeight() {
    height = std::max(LeftHeight(), RightHeight()) + 1;
  }

  NodePtr RotateRight() {
    if (!left) {
      return this;
    }
    if (parent) {
      parent->ReplaceChild(this, left);
    }
    left->SetParent(parent);
    auto left_child = left;
    SetLeftChild(left_child->right);
    left_child->SetRightChild(this);
    return left_child;
  }

  NodePtr RotateLeft() {
    if (!right) {
      return this;
    }
    if (parent) {
      parent->ReplaceChild(this, right);
    }
    right->SetParent(parent);
    auto right_child = right;
    SetRightChild(right_child->left);
    right_child->SetLeftChild(this);
    return right_child;
  }

  NodePtr Balance() {
    FixHeight();
    if (BalanceFactor() == 2) {
      if (right->BalanceFactor() < 0) {
        right = right->RotateRight();
      }
      return RotateLeft();
    }
    if (BalanceFactor() == -2) {
      if (left->BalanceFactor() > 0) {
        left = left->RotateLeft();
      }
      return RotateRight();
    }
    return this;
  }

  NodePtr Min() {
    if (left) {
      return left->Min();
    }
    return this;
  }

  NodePtr Max() {
    if (right) {
      return right->Max();
    }
    return this;
  }

 public:
  T value = T();
  NodePtr left = nullptr;
  NodePtr right = nullptr;
  NodePtr parent = nullptr;
  size_t height = 0;
};

template <class T>
class AvlTree {
 public:
  using Node = AvlTreeNode<T>;
  using NodePtr = Node*;
  using ConstNodePtr = const Node*;
  using CRef = const T&;

  ~AvlTree() {
    Clear();
  }

 protected:
  void ThrowIfTreeIsEmpty() const {
    if (!root_) {
      throw AvlTreeIsEmpty();
    }
  }

  void Clear(NodePtr start) {
    if (!start) {
      return;
    }
    Clear(start->left);
    Clear(start->right);
    delete start;
  }

  NodePtr Insert(NodePtr node, CRef value) {
    if (!node) {
      return new Node(value);
    }
    if (value < node->value) {
      node->left = Insert(node->left, value);
    } else if (value > node->value) {
      node->right = Insert(node->right, value);
    }
    return node->Balance();
  }

 public:
  void Clear() {
    Clear(root_);
    root_ = nullptr;
  }

  void Insert(CRef value) {
    root_ = Insert(root_, value);
  }

  T RemoveMin() {
    ThrowIfTreeIsEmpty(); 
    NodePtr min = root_->Min();
    T min_value = min->value;
    if (min->parent) {
      min->parent->SetLeftChild(min->right);
    } else {
      root_ = min->right;
    }
    delete min_value;
  }

  T GetMin() {
    ThrowIfTreeIsEmpty();
    return root_->Min()->value;
  }

  T RemoveMax() {
    ThrowIfTreeIsEmpty();
    NodePtr max = root_->Max();
    T max_value = max->value;
    if (max->parent) {
      max->parent->SetRightChild(max->left);
    } else {
      root_ = max->left;
    }
    delete max_value;
  }

  T GetMax() {
    ThrowIfTreeIsEmpty();
    return root_->Max()->value;
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


template <class T>
void Output(const T& value) {
  std::cout << value << std::endl;
}


void ErrorOutput() {
  Output("error");
}


void OkOutput() {
  std::cout << "ok";
}


using T = int64_t;
using Data = AvlTree<T>;


int main() {
  size_t n = 0;
  std::cin >> n;

  char command[200]{};

  Data deque;

  T argument = T();

  for (size_t i = 0; i < n; ++i) {
    std::cin >> command;

    try {
      if (command == "insert") {
        deque.Insert(InputResult<T>());
        OkOutput();
      } else if (command == "extract_min") {
        Output(deque.RemoveMin());
      } else if (command == "get_min") {
        Output(deque.GetMin());
      } else if (command == "extract_max") {
        Output(deque.RemoveMax());
      } else if (command == "get_max") {
        Output(deque.GetMax());
      } else if (command == "size") {
        Output(deque.Size());
      } else if (command == "clear") {
        deque.Clear();
        OkOutput();
      }
    } catch (...) {
      ErrorOutput();
    }
  }
}