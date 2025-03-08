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
  bool reversed;

  explicit Node(int64_t value)
      : count(1), priority(std::rand()), value(value), left(nullptr), right(nullptr), min(value), reversed(false) {
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
  tree->count = GetCount(tree->left) + GetCount(tree->right) + 1;
  tree->min = std::min(GetMin(tree->left), std::min(GetMin(tree->right), tree->value));
}

void PushReverse(Node* tree) {
  if (!tree || !tree->reversed) {
    return;
  }
  std::swap(tree->left, tree->right);
  if (tree->left) {
    tree->left->reversed = !tree->left->reversed;
  }
  if (tree->right) {
    tree->right->reversed = !tree->right->reversed;
  }
  tree->reversed = false;
}

std::pair<Node*, Node*> Split(Node* tree, int64_t index) {
  if (tree == nullptr) {
    return {nullptr, nullptr};
  }
  PushReverse(tree);
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
  PushReverse(left);
  PushReverse(right);
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

int64_t GetMin(Node*& tree, int64_t left_i, int64_t right_i) {
  auto [tmp, r] = Split(tree, right_i + 1);
  auto [l, mid] = Split(tmp, left_i);
  auto min = GetMin(mid);
  tree = Merge(l, mid);
  tree = Merge(tree, r);
  return min;
}

auto Reverse(Node* tree, int64_t left_i, int64_t right_i) {
  auto [tmp, r] = Split(tree, right_i + 1);
  auto [l, mid] = Split(tmp, left_i);
  mid->reversed = !mid->reversed;
  tree = Merge(l, mid);
  tree = Merge(tree, r);
  return tree;
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
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  char symb = 0;
  int64_t left = 0;
  int64_t right = 0;
  int64_t value = 0;
  Node* tree = nullptr;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> value;
    tree = Insert(tree, i, value);
  }
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> symb >> left >> right;
    --left;
    --right;
    if (symb == '1') {
      tree = Reverse(tree, left, right);
    }
    if (symb == '2') {
      std::cout << GetMin(tree, left, right) << "\n";
    }
  }
  Clear(tree);
}
