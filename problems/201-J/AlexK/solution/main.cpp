#include <cstdlib>
#include <iostream>
#include <utility>

struct Node {
  int64_t x;
  int64_t y;
  Node* left;
  Node* right;
  int64_t count;
};

int64_t GetCount(Node* tree) {
  if (tree == nullptr) {
    return 0;
  }
  return tree->count;
}

void UpdateCount(Node* tree) {
  tree->count = GetCount(tree->left) + GetCount(tree->right) + 1;
}

std::pair<Node*, Node*> Split(Node* tree, int64_t key) {
  if (tree == nullptr) {
    return {nullptr, nullptr};
  }
  if (key < tree->x) {
    auto result = Split(tree->left, key);
    tree->left = result.second;
    UpdateCount(tree);
    // tree->count = GetCount(result.second) + GetCount(tree->right) + 1;
    return {result.first, tree};
  }
  auto result = Split(tree->right, key);
  tree->right = result.first;
  UpdateCount(tree);
  // tree->count = GetCount(result.first) + GetCount(tree->left) + 1;
  return {tree, result.second};
}

Node* Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }
  if (left->y < right->y) {
    auto result = Merge(left, right->left);
    right->left = result;
    UpdateCount(right);
    // right->count = GetCount(right->left) + GetCount(right->right) + 1;
    return right;
  }
  auto result = Merge(left->right, right);
  left->right = result;
  UpdateCount(left);
  // left->count = GetCount(left->left) + GetCount(left->right) + 1;
  return left;
}

Node* Find(Node* tree, int64_t key) {
  if (tree == nullptr) {
    return nullptr;
  }
  if (tree->x == key) {
    return tree;
  }
  if (tree->x < key) {
    return Find(tree->right, key);
  }
  return Find(tree->left, key);
}

Node* Insert(Node* tree, int64_t key, int64_t priority) {
  if (Find(tree, key) != nullptr) {
    return tree;
  }
  Node* node = new Node(key, priority, nullptr, nullptr, 1);
  auto subtrees = Split(tree, key);
  tree = Merge(subtrees.first, node);
  tree = Merge(tree, subtrees.second);
  return tree;
}

Node* Delete(Node* tree, int64_t key) {
  if (Find(tree, key) == nullptr) {
    return tree;
  }
  auto [tmp, right] = Split(tree, key);
  auto [left, target] = Split(tmp, key - 1);
  delete target;
  return Merge(left, right);
}

Node* Kth(Node* tree, int64_t count) {
  if (tree == nullptr) {
    return nullptr;
  }
  auto left_count = GetCount(tree->left);
  if (left_count == count) {
    return tree;
  }
  if (count < left_count) {
    return Kth(tree->left, count);
  }
  return Kth(tree->right, count - left_count - 1);
}

Node* GetMin(Node* tree) {
  if (tree == nullptr) {
    return nullptr;
  }
  if (tree->left == nullptr) {
    return tree;
  }
  return GetMin(tree->left);
}

Node* GetMax(Node* tree) {
  if (tree == nullptr) {
    return nullptr;
  }
  if (tree->right == nullptr) {
    return tree;
  }
  return GetMax(tree->right);
}

Node* GetNext(Node*& tree, int64_t x) {
  auto split = Split(tree, x);
  auto min = GetMin(split.second);
  tree = Merge(split.first, split.second);
  return min;
}

Node* GetPrev(Node*& tree, int64_t x) {
  auto split = Split(tree, x);
  auto max = GetMax(split.first);
  tree = Merge(split.first, split.second);
  return max;
}

void Clear(Node* tree) {
  if (!tree) {
    return;
  }
  Clear(tree->left);
  Clear(tree->right);
  delete tree;
}

int main() {
  std::string command;
  int64_t value = 0;
  Node* tree = nullptr;
  std::srand(time(nullptr));
  while (std::cin >> command) {
    std::cin >> value;
    if (command == "insert") {
      tree = Insert(tree, value, std::rand());
    }
    if (command == "delete") {
      tree = Delete(tree, value);
    }
    if (command == "exists") {
      if (Find(tree, value) == nullptr) {
        std::cout << "false"
                  << "\n";
        continue;
      }
      std::cout << "true"
                << "\n";
    }
    if (command == "next") {
      auto next = GetNext(tree, value);
      if (next == nullptr) {
        std::cout << "none"
                  << "\n";
        continue;
      }
      std::cout << next->x << "\n";
    }
    if (command == "prev") {
      auto prev = GetPrev(tree, value);
      if (prev == nullptr) {
        std::cout << "none"
                  << "\n";
        continue;
      }
      std::cout << prev->x << "\n";
    }
    if (command == "kth") {
      // std::cout << value << '\n';
      auto count = Kth(tree, value);
      if (count == nullptr) {
        std::cout << "none"
                  << "\n";
        continue;
      }
      std::cout << count->x << "\n";
    }
  }
  Clear(tree);
}
