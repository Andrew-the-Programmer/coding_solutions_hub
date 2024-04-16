#include <iostream>

template <class T>
struct SplayNode {
 protected:
  using Node = SplayNode;
  using NodePtr = Node*;

 public:
  SplayNode() = default;

  SplayNode(const T& value, NodePtr parent, NodePtr left, NodePtr right)
      : value(value), parent(parent), left(left), right(right) {
  }

  explicit SplayNode(const T& value) : SplayNode(value, nullptr, nullptr, nullptr) {
  }

 public:
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

  static NodePtr Rotate(NodePtr parent, NodePtr child) {
    if (child == parent->left) {
      parent->RotateRight();
    } else if (child == parent->right) {
      parent->RotateLeft();
    }
    return child;
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

  NodePtr Splay() {
    if (parent == nullptr) {
      return this;
    }
    NodePtr gparent = parent->parent;
    if (!gparent) {
      return Rotate(parent, this);
    }
    bool zigzig = (gparent->left == parent) == (parent->left == this);
    if (zigzig) {
      Rotate(gparent, parent);
      Rotate(parent, this);
    } else {
      Rotate(parent, this);
      Rotate(gparent, this);
    }
    return Splay();
  }

  NodePtr Find(const T& value) {
    if (this->value == value) {
      return Splay();
    }
    if (value < this->value && left) {
      return left->Find(value);
    }
    if (value > this->value && right) {
      return right->Find(value);
    }
    return Splay();
  }

  NodePtr Max() {
    if (right) {
      return right->Max();
    }
    return this;
  }

  const Node* Next(const T& key) const {
    if (value == key) {
      return this;
    }
    if (key > value) {
      if (right) {
        return right->Next(key);
      }
      return nullptr;
    }
    if (!left) {
      return this;
    }
    if (left->Max()->value < key) {
      return this;
    }
    return left->Next(key);
  }

 public:
  T value = 0;
  NodePtr parent = nullptr;
  NodePtr left = nullptr;
  NodePtr right = nullptr;
};

template <class T>
class SplayTree {
 public:
  using Node = SplayNode<T>;
  using NodePtr = Node*;
  using SplitedTree = std::pair<NodePtr, NodePtr>;

 public:
  ~SplayTree() {
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
    root_ = nullptr;
  }

  SplitedTree Split(const T& value) {
    auto root = root_->Find(value);
    NodePtr left = nullptr;
    NodePtr right = nullptr;
    if (root->value == value) {
      left = root->left;
      right = root->right;
      delete root;
      // throw std::logic_error("");

      // left = root->left;
      // right = root->right;
      // Node::Split(root, root->left);
      // Node::Split(root, root->right);
      // delete root;
    } else if (value < root->value) {
      left = root->left;
      right = root;
      Node::Split(root, root->left);
    } else if (root->value < value) {
      left = root;
      right = root->right;
      Node::Split(root, root->right);
    }
    return {left, right};
  }

  void Add(const T& value) {
    if (!root_) {
      root_ = new Node(value);
      return;
    }
    auto splited = Split(value);
    root_ = new Node(value, nullptr, splited.first, splited.second);
    root_->KeepParent();
  }

  T Next(const T& value) const {
    if (!root_) {
      return -1;
    }
    auto next = root_->Next(value);
    if (next) {
      return next->value;
    }
    return -1;
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
using Tree = SplayTree<T>;
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