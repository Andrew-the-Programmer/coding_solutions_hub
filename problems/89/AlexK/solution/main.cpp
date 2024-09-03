#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int32_t second;
  int32_t weight;
  int32_t index;
};

class DSU {
 private:
  std::vector<size_t> parents_;
  std::vector<size_t> heights_;
  std::vector<int64_t> weights_;

 public:
  explicit DSU(size_t n) : parents_(n), heights_(n, 0), weights_(n, 0) {
    for (size_t i = 0; i < n; ++i) {
      parents_[i] = i;
    }
  }

  size_t Find(size_t index) {
    if (parents_[index] == index) {
      return index;
    }
    parents_[index] = Find(parents_[index]);
    return parents_[index];
  }

  bool SameGroup(size_t index_1, size_t index_2) {
    return Find(index_1) == Find(index_2);
  }

  void Unite(size_t index_1, size_t index_2, int64_t weight) {
    if (SameGroup(index_1, index_2)) {
      weights_[Find(index_1)] += weight;
      return;
    }
    size_t parent_1 = Find(index_1);
    size_t parent_2 = Find(index_2);
    int64_t weight_1 = weights_[parent_1];
    int64_t weight_2 = weights_[parent_2];
    if (heights_[parent_1] > heights_[parent_2]) {
      parents_[parent_2] = parent_1;
    } else if (heights_[parent_1] < heights_[parent_2]) {
      parents_[parent_1] = parent_2;
    } else {
      parents_[parent_2] = parent_1;
      ++heights_[parent_1];
    }
    weights_[Find(index_1)] = weight_1 + weight_2 + weight;
  }

  int64_t GetWeight(size_t index) {
    return weights_[Find(index)];
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int32_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  DSU dsu(n);
  for (size_t i = 0; i < m; ++i) {
    int32_t command = 0;
    std::cin >> command;
    if (command == 1) {
      int32_t from = 0;
      int32_t to = 0;
      int32_t weight = 0;
      std::cin >> from >> to >> weight;
      --from;
      --to;
      dsu.Unite(from, to, weight);
    }
    if (command == 2) {
      int32_t from = 0;
      std::cin >> from;
      --from;
      std::cout << dsu.GetWeight(from) << "\n";
    }
  }
}
