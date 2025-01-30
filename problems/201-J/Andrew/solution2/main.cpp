#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

class Treap {
  struct Node {
    int key;
    int priority;
    int cnt = 1;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int key, int priority) : key(key), priority(priority) {
    }
    Node() : key(0), priority(0) {
    }
  };

  int KthHelper(std::shared_ptr<Node> current, int k) const {
    if (!current) {
      return -1;
    }
    int left = Count(current->left);
    if (k == left + 1) {
      return current->key;
    }
    if (k <= left) {
      return KthHelper(current->left, k);
    }
    return KthHelper(current->right, k - left - 1);
  }

  std::shared_ptr<Node> root_;

 public:
  Treap() : root_(nullptr) {
  }

  std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Split(std::shared_ptr<Node> node, int key) {
    if (!node) {
      return {nullptr, nullptr};
    }
    if (key > node->key) {
      auto pair = Split(node->right, key);
      node->right = pair.first;
      UpdateCount(node);
      return {node, pair.second};
    }
    auto pair = Split(node->left, key);
    node->left = pair.second;
    UpdateCount(node);
    return {pair.first, node};
  }

  void Insert(int key, int priority) {
    if (Contains(key)) {
      return;
    }
    std::shared_ptr<Node> new_node = std::make_shared<Node>(key, priority);
    std::shared_ptr<Node> current = root_;
    std::shared_ptr<Node> parent = nullptr;
    if (!current) {
      root_ = new_node;
      return;
    }
    while (current && priority <= current->priority) {
      parent = current;
      parent->cnt++;
      current = (current->key < key ? current->right : current->left);
    }
    if (!current) {
      if (parent->key < key) {
        parent->right = new_node;
      } else {
        parent->left = new_node;
      }
      return;
    }
    auto pair = Split(current, key);
    new_node->left = pair.first;
    new_node->right = pair.second;
    UpdateCount(new_node);
    if (!parent) {
      root_ = new_node;
      return;
    }
    if (parent->key < key) {
      parent->right = new_node;
    } else {
      parent->left = new_node;
    }
  }

  std::shared_ptr<Node> Merge(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    if (!left) {
      return right;
    }
    if (!right) {
      return left;
    }
    if (left->priority > right->priority) {
      left->right = Merge(left->right, right);
      UpdateCount(left);
      return left;
    }
    right->left = Merge(left, right->left);
    UpdateCount(right);
    return right;
  }

  void Erase(int key) {
    if (!Contains(key)) {
      return;
    }
    std::shared_ptr<Node> current = root_;
    std::shared_ptr<Node> parent = nullptr;
    while (current && current->key != key) {
      parent = current;
      parent->cnt--;
      current = (current->key < key ? current->right : current->left);
    }
    current = Merge(current->left, current->right);
    if (!parent) {
      root_ = current;
      return;
    }
    if (parent->key < key) {
      parent->right = current;
    } else {
      parent->left = current;
    }
  }

  bool Contains(int key) const {
    std::shared_ptr<Node> current = root_;
    if (!current) {
      return false;
    }
    while (current->key != key) {
      current = (current->key < key ? current->right : current->left);
      if (!current) {
        return false;
      }
    }
    return true;
  }

  int Next(int key) const {
    std::shared_ptr<Node> current = root_;
    if (!current) {
      return -1;
    }
    while (current->key <= key && current->right) {
      current = current->right;
    }
    while (current->left && current->left->key >= key) {
      current = current->left;
    }
    if (current->key < key) {
      return -1;
    }
    return current->key;
  }

  int Prev(int key) const {
    std::shared_ptr<Node> current = root_;
    if (!current) {
      return -1;
    }
    while (current->key >= key && current->left) {
      current = current->left;
    }
    while (current->right && current->right->key <= key) {
      current = current->right;
    }
    if (current->key > key) {
      return -1;
    }
    return current->key;
  }

  int Count(std::shared_ptr<Node> current) const {
    if (!current) {
      return 0;
    }
    return current->cnt;
  }

  void UpdateCount(std::shared_ptr<Node> current) {
    if (!current) {
      return;
    }
    current->cnt = Count(current->left) + Count(current->right) + 1;
  }

  int Kth(int key) const {
    return KthHelper(root_, key + 1);
  }
};

int main() {
  int temp = 0;
  std::string str;
  Treap treap;
  while (std::cin >> str) {
    std::cin >> temp;
    if (str == "insert") {
      treap.Insert(temp, std::rand());
    } else if (str == "delete") {
      treap.Erase(temp);
    } else if (str == "exists") {
      std::cout << (treap.Contains(temp) ? "true\n" : "false\n");
    } else if (str == "next") {
      int val = treap.Next(temp);
      if (val == -1) {
        std::cout << "none\n";
      } else {
        std::cout << val << '\n';
      }
    } else if (str == "prev") {
      int val = treap.Prev(temp);
      if (val == -1) {
        std::cout << "none\n";
      } else {
        std::cout << val << '\n';
      }
    } else if (str == "kth") {
      int val = treap.Kth(temp);
      if (val == -1) {
        std::cout << "none\n";
      } else {
        std::cout << val << '\n';
      }
    }
  }
  return 0;
}
