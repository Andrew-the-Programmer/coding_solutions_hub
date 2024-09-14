#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

using NodeType = uint32_t;
using WeightType = uint32_t;

struct Edge {
  NodeType from;
  NodeType to;
  WeightType weight;

  Edge() = default;
  Edge(NodeType from, NodeType to, WeightType weight) : from(from), to(to), weight(weight) {
  }
};

class DSU {
 public:
  explicit DSU(size_t size) : size_(size), parent_(size), rank_(size, 0), mass_(size, 0) {
    for (NodeType i = 0; i < size; ++i) {
      MakeSet(i);
    }
  }

 public:
  void MakeSet(NodeType node) {
    parent_[node] = node;
    rank_[node] = 0;
  }

  NodeType FindSet(NodeType node) {
    if (node == parent_[node]) {
      return node;
    }
    return parent_[node] = FindSet(parent_[node]);
  }

  void Hang(NodeType node, NodeType root, WeightType weight) {
    // hang node to root
    parent_[node] = root;
    mass_[root] += mass_[node] + weight;
  }

  void Union(const Edge& edge) {
    auto from = FindSet(edge.from);
    auto to = FindSet(edge.to);
    if (from == to) {
      mass_[from] += edge.weight;
      return;
    }
    if (rank_[from] >= rank_[to]) {
      Hang(to, from, edge.weight);
      if (rank_[from] == rank_[to]) {
        ++rank_[from];
      }
    } else {
      Hang(from, to, edge.weight);
    }
  }

  WeightType GetMass(NodeType node) {
    return mass_[node];
  }

 protected:
  size_t size_{};
  std::vector<NodeType> parent_{};
  std::vector<size_t> rank_{};
  std::vector<WeightType> mass_{};
};

void SetIostream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  SetIostream();

  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  DSU dsu(n);
  for (size_t i = 0; i < m; ++i) {
    size_t operation{};
    std::cin >> operation;
    switch (operation) {
      case 1: {
        NodeType from{};
        NodeType to{};
        WeightType weight{};
        std::cin >> from >> to >> weight;
        --from;
        --to;
        dsu.Union({from, to, weight});
        break;
      }
      case 2: {
        NodeType node{};
        std::cin >> node;
        --node;
        auto root = dsu.FindSet(node);
        std::cout << dsu.GetMass(root) << '\n';
        break;
      }
    }
  }
  return 0;
}
