#include <iostream>

template <class T>
struct AvlTreeNode {
  using Node = AvlTreeNode;
  using NodePtr = Node*;
  using ConstNodePtr = const Node*;
  using CRef = const T&;

  explicit AvlTreeNode(CRef value = T()) : value(value), height(1) {
  }

  ConstNodePtr Max() const {
    if (right) {
      return right->Max();
    }
    return this;
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
      return nullptr;
    }

    NodePtr left_child = left;
    left = left_child->right;
    left_child->right = this;

    FixHeight();
    left_child->FixHeight();

    return left_child;
  }

  NodePtr RotateLeft() {
    if (!right) {
      return nullptr;
    }

    NodePtr right_child = right;
    right = right_child->left;
    right_child->left = this;

    FixHeight();
    right_child->FixHeight();

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

 public:
  T value = T();
  NodePtr left = nullptr;
  NodePtr right = nullptr;
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
  void Clear(NodePtr start) {
    if (!start) {
      return;
    }
    Clear(start->left);
    Clear(start->right);
    delete start;
  }

  NodePtr Add(NodePtr node, CRef value) {
    if (!node) {
      return new Node(value);
    }
    if (value < node->value) {
      node->left = Add(node->left, value);
    } else if (value > node->value) {
      node->right = Add(node->right, value);
    }
    return node->Balance();
  }

  T Next(ConstNodePtr start, CRef value) const {
    if (!start) {
      return -1;
    }
    if (value == start->value) {
      return value;
    }
    if (value > start->value) {
      return Next(start->right, value);
    }
    if (start->left) {
      if (start->left->Max()->value < value) {
        return start->value;
      }
      return Next(start->left, value);
    }
    return start->value;
  }

 public:
  void Clear() {
    Clear(root_);
    root_ = nullptr;
  }

  void Add(CRef value) {
    root_ = Add(root_, value);
  }

  T Next(CRef value) const {
    return Next(root_, value);
  }

 protected:
  NodePtr root_ = nullptr;
};

template <class T, class U>
struct Command {
  char name = 0;
  T argument = T();
  U result = U();

  Command() = default;

  friend std::istream& operator>>(std::istream& stream, Command& cmd) {
    stream >> cmd.name >> cmd.argument;
    cmd.result = U();
    return stream;
  }
};

using T = int64_t;
using Tree = AvlTree<T>;
using Cmd = Command<T, T>;

int main() {
  const T limit = 1e9;

  Tree tree;

  size_t n = 0;
  std::cin >> n;

  Cmd command;
  Cmd last_command;

  for (size_t i = 0; i < n; ++i, last_command = command) {
    std::cin >> command;
    switch (command.name) {
      case '+': {
        if (last_command.name == '+' || last_command.name == 0) {
          tree.Add(command.argument);
        } else if (last_command.name == '?') {
          tree.Add((command.argument + last_command.result) % limit);
        }
        break;
      }
      case '?': {
        command.result = tree.Next(command.argument);
        std::cout << command.result << std::endl;
        break;
      }
      default: {
        break;
      }
    }
  }
}