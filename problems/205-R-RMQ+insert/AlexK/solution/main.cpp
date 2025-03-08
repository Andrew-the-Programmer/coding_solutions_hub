#include <cstdint>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <limits>

int64_t k_ind = std::numeric_limits<int64_t>::max();

struct Node {
  int64_t count;
  int64_t priority;
  int64_t value;
  Node* left;
  Node* right;
  int64_t min;

  explicit Node(int64_t value) : count(1), priority(std::rand()), value(value), left(nullptr), right(nullptr), min(value) {
  }
};

int64_t GetCount(Node* tree) {
  if (tree == nullptr) {
    return 0;
  }
  return tree->count;
}

int64_t GetMin(Node* tree) {
  if (tree == nullptr) {
    return k_ind;
  }
  return tree->min;
}

void Update(Node* tree) {
  if (tree == nullptr) {
    return;
  }
  tree->count = GetCount(tree->left) + GetCount(tree->right) + 1;
  tree->min = std::min(GetMin(tree->left), std::min(GetMin(tree->right), tree->value));
}

std::pair<Node*, Node*> Split(Node* tree, int64_t index) {
  if (tree == nullptr) {
    return {nullptr, nullptr};
  }
  if (index <= GetCount(tree->left)) {
    auto result = Split(tree->left, index);
    tree->left = result.second;
    Update(tree);
    return {result.first, tree};
  }
  auto result = Split(tree->right, index - GetCount(tree->left) - 1);
  tree->right = result.first;
  Update(tree);
  return {tree, result.second};
}

Node* Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }
  if (left->priority < right->priority) {
    auto result = Merge(left, right->left);
    right->left = result;
    Update(right);
    return right;
  }
  auto result = Merge(left->right, right);
  left->right = result;
  Update(left);
  return left;
}

Node* Insert(Node* tree, int64_t index, int64_t value) {
  Node* node = new Node(value);
  auto subtrees = Split(tree, index);
  tree = Merge(subtrees.first, node);
  tree = Merge(tree, subtrees.second);
  return tree;
}

int64_t GetMinOnSegment(Node*& tree, int64_t left_i, int64_t right_i) {
  auto left_subtr = Split(tree, left_i);
  auto right_subtr = Split(left_subtr.second, right_i + 1);
  auto min = GetMin(right_subtr.first);
  tree = Merge(right_subtr.first, right_subtr.second);
  tree = Merge(left_subtr.first, tree);
  return min;
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
  std::srand(time(nullptr));
  size_t n = 0;
  std::cin >> n;
  char symb = 0;
  int64_t left = 0;
  int64_t right = 0;
  int64_t count = 0;
  int64_t value = 0;
  Node* tree = nullptr;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> symb;
    if (symb == '+') {
      std::cin >> count >> value;
      tree = Insert(tree, count, value);
    }
    if (symb == '?') {
      std::cin >> left >> right;
      --left;
      --right;
      std::cout << GetMinOnSegment(tree, left, right);
    }
  }
  Clear(tree);
}
