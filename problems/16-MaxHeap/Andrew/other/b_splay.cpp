template <class T>
struct SplayNode {
//-----------------------------------------------------
public:
  using value_type = T;
//-----------------------------------------------------
protected:
  using node = SplayNode;
  using node_ptr = node*;
  using npc = node_ptr const;
  using cnpc = const node * const;
  using cvtr = const value_type &;
  using SplitedTree = std::pair <node_ptr, node_ptr>;
//-----------------------------------------------------
public:
  SplayNode () = default;
  SplayNode (const value_type& value, npc parent, npc left, npc right) 
  : value (value)
  , parent (parent)
  , left (left)
  , right (right)
  {}
  SplayNode (const value_type value) 
  : SplayNode (value, nullptr, nullptr, nullptr) {}

  ~SplayNode () {
    if (left) {left->SetParent(nullptr);}
    if (right) {right->SetParent(nullptr);}
    if (parent) {parent->ReplaceChild(this, nullptr);}
    delete &value;
  }
//-----------------------------------------------------
public:
  void PushRight (cvtr value) {
    if (right == nullptr) {
      right = new node (value);
      right->parent = this;
    }
  }
  void PushLeft (cvtr value) {
    if (right == nullptr) {
      left = new node (value);
      left->parent = this;
    }
  }

  void SetParent (node_ptr parent) {
    this->parent = parent;
  }
  void KeepParent () {
    if (left)  {left->SetParent(this);}
    if (right) {right->SetParent(this);}
  }

  void SetRightChild (npc child) {
    right = child;
    if (child) {
      child->parent = this;
    }
  } 
  void SetLeftChild (npc child) {
    left = child;
    if (child) {
      child->parent = this;
    }
  }

  void ReplaceChild (npc old_child, npc new_child) {
    if (left == old_child) {
      SetLeftChild (new_child);
    } else if (right == old_child) {
      SetRightChild (new_child);
    }
  }

  node_ptr RotateRight () {
    if (!left) {
      return this;
    }
    if (parent) {
      parent->ReplaceChild(this, left);
    }
    auto left_child = left;
    SetLeftChild (left_child->right);
    left_child->SetRightChild (this);
    return left_child;
  }
  node_ptr RotateLeft () {
    if (!right) {
      return this;
    }
    if (parent) {
      parent->ReplaceChild(this, right);
    }
    auto right_child = right;
    SetRightChild (right_child->left);
    right_child->SetLeftChild (this);
    return right_child;
  }

  static node_ptr Rotate (npc parent, npc child) {
    if (child == parent->left) {
      parent->RotateRight();
    } else if (child == parent->right) {
      parent->RotateLeft();
    }
    return child;
  }
  static void Split (npc parent, npc child) {
    if (child == parent->left) {
      child->SetParent(nullptr);
      parent->SetLeftChild(nullptr);
    } else if (child == parent->right) {
      child->SetParent(nullptr);
      parent->SetRightChild(nullptr);
    }
  }

  node_ptr Zig () {
    if (parent) {
      parent->RotateRight();
    }
    return this;
  }
  node_ptr Zag () {
    if (parent) {
      parent->RotateLeft();
    }
    return this;
  }
  node_ptr Zug () {
    if (parent) {
      if (this == parent->left) {
        return Zig();
      } else if (this == parent->right) {
        return Zag();
      }
    }
    return this;
  }
  node_ptr ZigZig () {
    return Zag()->Zig();
  }
  node_ptr ZagZag () {
    return Zig()->Zag();
  }
  node_ptr ZigZag () {
    if (parent) {
      parent->RotateLeft();
    }
    auto gparent = parent->parent;
    if (gparent) {
      gparent->RotateRight();
    }
  }
  node_ptr ZugZug () {
    return Zug()->Zug();
  }
  
  node_ptr Splay (cnpc finish = nullptr) {
    if (this == finish) {
      return this;
    }
    if (parent) {
      if (parent == finish) {
        return Zug();
      }
      return Zug()->Splay();
    }
    return this;
  }
  
  node_ptr Find (cvtr value, cnpc finish = nullptr) {
    if (this->value == value) {
      return Splay(finish);
    }
    if (value < this->value && left) {
      return left->Find (value, finish);
    }
    if (value > this->value && right) {
      return left->Find (value, finish);
    }
    return Splay(finish);
  }

  SplitedTree Split (cvtr value, cnpc finish = nullptr) {
    auto root = Find(value, finish);
    node_ptr left = nullptr;
    node_ptr right = nullptr;
    if (root->value == value) {
      left = root->left;
      right = root->right;
      root->~node();
    } else if (value < root->value) {
      left = root;
      right = root->right;
      node::Split (root, right);
    } else if (root->value < value) {
      left = root->left;
      right = root;
      node::Split (root->left, root);
    }
    return {left, right};
  }

  node_ptr Insert (value_type key) {
    if (key < value && left) {
      left->Insert(key);
    } else if (key > value && right) {
      right = Insert(key);
    }
    return Balance();
  }

  node_ptr FindMin () {
    return left ? left->FindMin() : this;
  }

  node_ptr RemoveMin () {}
  
  node_ptr Remove (const value_type& _key) {
    if (_key < value && left) {
      left = left->Remove(_key);
    } else if (_key > value && right) {
      right = right->Remove(_key);
    } else if (_key == value) {
      node_ptr left = this->left;
      node_ptr right = this->left;
      ~this;
      if (right == nullptr) {return left;}
      node_ptr min = right->FindMin();
      min->right = RemoveMin();
      min->left = left;
      return Balance(min);
    }
    return Balance();
  }
//-----------------------------------------------------
protected:
  node_ptr next1() const {}
//-----------------------------------------------------
public:
  value_type get_value() {return value;}
  node_ptr next() const {

  }
//-----------------------------------------------------
public:
  value_type value;
  node_ptr parent;
  node_ptr left;
  node_ptr right;
};

template <class T>
class SplayTree {
//---------------------------------------------------
public:
  using value_type = T;
  using node = SplayNode<value_type>;
  using iterator = my::Iterator::OutputIterator<node>;
//-----------------------------------------------------
protected:
  using node_ptr = node*;
  using npc = node_ptr const;
  using cnpc = const node * const;
  using cvtr = const value_type &;
//-----------------------------------------------------
public:
  SplayTree () {}
//-----------------------------------------------------
public:
  void Insert (cvtr value) {
    auto splited = root_->Split(value);
    root_ = new node (value, nullptr, splited.first, splited.second);
    root_->KeepParent();
  }

//-----------------------------------------------------
protected:
  node_ptr root_;
};

int main() {
  int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n;
  int64_t m;
  int64_t size = 0;
  int64_t command;
  std::cin >> n >> m;
  auto* arr = new int64_t[n + 100];
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> command;
    if (command == 1) {
      if (size < 1) {
        std::cout << -1 << '\n';
      } else if (size == 1) {
        std::cout << 0 << " " << arr[0] << '\n';
        --size;
      } else {
        int64_t first_arr = arr[0];
        std::cout << PopHeap(arr, size) + 1 << " " << first_arr << '\n';
        --size;
      }
    }
    if (command == 2) {
      if (size == n) {
        int64_t okey;
        std::cin >> okey;
        std::cout << -1 << '\n';
      } else {
        std::cin >> arr[size];
        std::cout << PushHeap(arr, size) + 1 << '\n';
        ++size;
      }
    }
    if (command == 3) {
      int64_t plase;
      std::cin >> plase;
      if (plase - 1 >= size || size == 0 || plase < 1) {
        std::cout << -1 << '\n';
      } else {
        std::cout << PopAny(arr, plase - 1, size) << '\n';
        --size;
      }
    }
  }
  for (int64_t j = 0; j < size; ++j) {
    std::cout << arr[j] << " ";
  }
  delete[] arr;
}
}