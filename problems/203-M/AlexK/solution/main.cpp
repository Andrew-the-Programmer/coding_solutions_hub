#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

using Int = uint32_t;

struct Node {
  Int value = 0;
  Int promise = 0;
};

struct SegmentTree {
  size_t n = 1 << 24;
  std::vector<Node> tree;

  SegmentTree() = default;

  size_t Left(size_t node) const {
    return node * 2 + 1;
  }

  size_t Right(size_t node) const {
    return node * 2 + 2;
  }

  void Build() {
    tree.resize(2 * n - 1, {0, 0});
  }

  void Push(size_t node, size_t tree_domain) {
    tree[node].value += tree[node].promise * static_cast<Int>(tree_domain);
    if (static_cast<size_t>(Left(node)) < tree.size()) {
      tree[Left(node)].promise += tree[node].promise;
    }
    if (static_cast<size_t>(Right(node)) < tree.size()) {
      tree[Right(node)].promise += tree[node].promise;
    }
    tree[node].promise = 0;
  }

  void Update(size_t l, size_t r, size_t node, size_t node_l, size_t node_r, Int delta) {
    // std::cout << node << ' ' << node_l << ' ' << node_r << '\n';
    // std::cout << "0\n";
    size_t tree_domain = node_r - node_l + 1;
    // Push(node, tree_domain);
    Push(node, tree_domain);
    if (node_l > r || node_r < l) {
      return;
    }
    if (l <= node_l && r >= node_r) {
      tree[node].promise += delta;
      Push(node, tree_domain);
      return;
    }
    size_t mid = (node_l + node_r) / 2;
    Update(l, r, Left(node), node_l, mid, delta);
    Update(l, r, Right(node), mid + 1, node_r, delta);
    tree[node].value = tree[Left(node)].value + tree[Right(node)].value;
  }

  Int Query(size_t l, size_t r, size_t node, size_t node_l, size_t node_r) {
    size_t tree_domain = node_r - node_l + 1;
    if (node_l > r || node_r < l) {
      return 0;
    }
    Push(node, tree_domain);
    if (l <= node_l && node_r <= r) {
      return tree[node].value;
    }
    size_t mid = (node_l + node_r) / 2;
    Int left_r = Query(l, r, Left(node), node_l, mid);
    Int right_r = Query(l, r, Right(node), mid + 1, node_r);
    return left_r + right_r;
  }

  void Update(size_t l, size_t r, Int delta) {
    Update(l, r, 0, 0, n - 1, delta);
  }

  Int Query(size_t l, size_t r) {
    return Query(l, r, 0, 0, n - 1);
  }
};

Int NextRand(Int a, Int b, Int& cur) {
  cur = cur * a + b;
  return cur >> 8;
}

int main() {
  size_t m = 0;
  size_t q = 0;
  std::cin >> m >> q;
  Int a = 0;
  Int b = 0;
  Int curr = 0;
  std::cin >> a >> b;
  SegmentTree tree;
  tree.Build();
  for (size_t i = 0; i < m; ++i) {
    auto delta = NextRand(a, b, curr);
    auto left = NextRand(a, b, curr);
    auto right = NextRand(a, b, curr);
    // std::cout << left << ' ' << right << '\n';
    if (left > right) {
      std::swap(left, right);
    }
    tree.Update(left, right, delta);
  }
  Int sum = 0;
  for (size_t i = 0; i < q; ++i) {
    auto left = NextRand(a, b, curr);
    auto right = NextRand(a, b, curr);
    if (left > right) {
      std::swap(left, right);
    }
    // auto q = tree.Query(left, right);
    // std::cout << q << '\n';
    sum += tree.Query(left, right);
  }
  std::cout << sum << '\n';
}
