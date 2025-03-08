#include <iostream>
#include <limits>
#include <optional>
#include <vector>
#include <boost/format.hpp>

int64_t k_inf = std::numeric_limits<int64_t>::max();

struct Node {
  int64_t value;
};

struct SegmentTree {
  std::vector<Node> tree;
  int64_t n = 0;
  SegmentTree() = default;

  int64_t Left(int64_t node) const {
    return node * 2 + 1;
  }

  int64_t Right(int64_t node) const {
    return node * 2 + 2;
  }

  void Build(const std::vector<int64_t>& vec) {
    n = 1;
    while (n < static_cast<int64_t>(vec.size())) {
      n *= 2;
    }
    tree.resize(2 * n - 1, {0});
    for (size_t i = 0; i < vec.size(); ++i) {
      tree[n - 1 + i].value = vec[i];
    }
    for (int64_t i = n - 2; i >= 0; --i) {
      tree[i].value = std::min(tree[i * 2 + 1].value, tree[i * 2 + 2].value);
    }
  }

  int64_t Query(int64_t l, int64_t r, int64_t node, int64_t node_l, int64_t node_r) {
    if (l <= node_l && node_r <= r) {
      return tree[node].value;
    }
    if (node_l > r || node_r < l) {
      return k_inf;
    }
    int64_t mid = (node_l + node_r) / 2;
    int64_t left_r = Query(l, r, Left(node), node_l, mid);
    int64_t right_r = Query(l, r, Right(node), mid + 1, node_r);
    return std::min(left_r, right_r);
  }

  int64_t Query(int64_t l, int64_t r) {
    return Query(l, r, 0, 0, n - 1);
  }
};

struct ST2D {
  std::vector<SegmentTree> table;

  ST2D() = default;

  void Build2D(const std::vector<std::vector<int64_t>>& matrix) {
    table.resize(matrix.size());
    for (size_t i = 0; i < matrix.size(); ++i) {
      table[i].Build(matrix[i]);
    }
  }

  int64_t Query2D(int64_t x1, int64_t x2, int64_t y1, int64_t y2) {
    std::cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
    if (y1 == y2) {
      std::cout << "query: " << table[y1].Query(x1, x2) << "\n";
      return table[y1].Query(x1, x2);
    }
    int64_t mid = (y1 + y2) / 2;
    auto min_1 = Query2D(x1, x2, y1, mid);
    auto min_2 = Query2D(x1, x2, mid + 1, y2);
    return std::min(min_1, min_2);
  }
};

int main() {
  size_t m = 0;
  size_t n = 0;
  std::cin >> m >> n;
  std::vector<std::vector<int64_t>> matrix(m);
  for (size_t i = 0; i < m; ++i) {
    matrix[i].resize(n);
    for (size_t j = 0; j < n; ++j) {
      std::cin >> matrix[i][j];
    }
  }
  ST2D table;
  table.Build2D(matrix);
  int64_t requests = 0;
  std::cin >> requests;
  int64_t x1 = 0;
  int64_t x2 = 0;
  int64_t y1 = 0;
  int64_t y2 = 0;
  for (int64_t i = 0; i < requests; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    --x1;
    --y1;
    --x2;
    --y2;
    std::cout << table.Query2D(x1, x2, y1, y2) << '\n';
  }
}
