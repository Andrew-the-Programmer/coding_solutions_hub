#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

struct Node {
  uint32_t value = 0;
  uint32_t promise = 0;
};

struct SegmentTree {
  int64_t n = 1 << 24;
  std::vector<Node> tree;

  SegmentTree() = default;

  int64_t Left(int64_t node) const {
    return node * 2 + 1;
  }

  int64_t Right(int64_t node) const {
    return node * 2 + 2;
  }

  void Build() {
    tree.resize(2 * n - 1, {0, 0});
  }

  void Push(int64_t node, int64_t node_l, int64_t node_r) {
    tree[node].value += tree[node].promise * (node_r - node_l + 1);
    if (static_cast<size_t>(Left(node)) < tree.size()) {
      tree[Left(node)].promise += tree[node].promise;
    }
    if (static_cast<size_t>(Right(node)) < tree.size()) {
      tree[Right(node)].promise += tree[node].promise;
    }
    tree[node].promise = 0;
  }

  void Update(int64_t l, int64_t r, int64_t node, int64_t node_l, int64_t node_r, uint32_t delta) {
    Push(node, node_l, node_r);
    if (l <= node_l && r >= node_r) {
      tree[node].promise += delta;
      Push(node, node_l, node_r);
      return;
    }
    if (node_l > r || node_r < l) {
      return;
    }
    int64_t mid = (node_l + node_r) / 2;
    Update(l, r, Left(node), node_l, mid, delta);
    Update(l, r, Right(node), mid + 1, node_r, delta);
    tree[node].value = tree[Left(node)].value + tree[Right(node)].value;
  }

  uint32_t Query(int64_t l, int64_t r, int64_t node, int64_t node_l, int64_t node_r) {
    if (node_l > r || node_r < l) {
      return 0;
    }
    Push(node, node_l, node_r);
    if (l <= node_l && node_r <= r) {
      return tree[node].value;
    }
    int64_t mid = (node_l + node_r) / 2;
    auto left_r = Query(l, r, Left(node), node_l, mid);
    auto right_r = Query(l, r, Right(node), mid + 1, node_r);
    return left_r + right_r;
  }

  void Update(int64_t l, int64_t r, int64_t delta) {
    Update(l, r, 0, 0, n - 1, delta);
  }

  int64_t Query(int64_t l, int64_t r) {
    return Query(l, r, 0, 0, n - 1);
  }
};

uint32_t NextRand(uint32_t a, uint32_t b, uint32_t& cur) {
  cur = cur * a + b;
  return cur >> 8;
}

int main() {
  int64_t m = 0;
  int64_t q = 0;
  std::cin >> m >> q;
  uint32_t a = 0;
  uint32_t b = 0;
  uint32_t curr = 0;
  std::cin >> a >> b;
  SegmentTree tree;
  tree.Build();
  for (int64_t i = 0; i < m; ++i) {
    auto delta = NextRand(a, b, curr);
    auto left = NextRand(a, b, curr);
    auto right = NextRand(a, b, curr);
    if (left > right) {
      std::swap(left, right);
    }
    tree.Update(left, right, delta);
  }
  uint32_t sum = 0;
  for (int64_t i = 0; i < q; ++i) {
    auto left = NextRand(a, b, curr);
    auto right = NextRand(a, b, curr);
    if (left > right) {
      std::swap(left, right);
    }
    sum += tree.Query(left, right);
  }
  std::cout << sum << '\n';
}
