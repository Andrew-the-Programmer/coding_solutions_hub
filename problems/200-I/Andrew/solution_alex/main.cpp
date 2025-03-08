#include <iostream>
#include <vector>

struct Node {
  int64_t x;
  int64_t y;
  Node* left;
  Node* right;
  Node* parent;
};
Node* Build(std::vector<Node>& data) {
  Node* root = &data.front();
  Node* curr = root;
  for (size_t i = 1; i < data.size(); ++i) {
    Node* ptr = &data[i];
    while (curr->y > ptr->y) {
      curr = curr->parent;
      if (curr == nullptr) {
        break;
      }
    }
    if (curr == nullptr) {
      ptr->left = root;
      root->parent = ptr;
      root = ptr;
      curr = root;
      continue;
    }
    if (curr->right == nullptr) {
      curr->right = ptr;
      ptr->parent = curr;
      curr = curr->right;
      continue;
    }
    ptr->left = curr->right;
    ptr->parent = curr;
    ptr->left->parent = ptr;
    curr->right = ptr;
    curr = curr->right;
  }
  return root;
}

void PreOrderPrint(Node* tree) {
  if (tree == nullptr) {
    return;
  }
  PreOrderPrint(tree->left);
  if (tree->parent != nullptr) {
    std::cout << tree->parent->x + 1 << " ";
  } else {
    std::cout << 0 << " ";
  }
  if (tree->left != nullptr) {
    std::cout << tree->left->x + 1 << " ";
  } else {
    std::cout << 0 << " ";
  }
  if (tree->right != nullptr) {
    std::cout << tree->right->x + 1;
  } else {
    std::cout << 0;
  }
  std::cout << "\n";
  PreOrderPrint(tree->right);
}

int main() {
  int64_t n = 0;
  std::cin >> n;
  std::vector<Node> vec(n, {0, 0, nullptr, nullptr, nullptr});
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> vec[i].x >> vec[i].y;
  }
  auto tree = Build(vec);
  std::cout << "YES" << "\n";
  PreOrderPrint(tree);
}
