#include <cstddef>
#include <iostream>
#include <vector>

using NodeType = size_t;
using WeightType = size_t;

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
  explicit DSU(size_t size) : size(size), parent(size), rank(size, 0), mass(size, 0) {
    for (NodeType i = 0; i < size; ++i) {
      MakeSet(i);
    }
  }

 public:
  void MakeSet(NodeType node) {
    parent[node] = node;
    rank[node] = 0;
  }

  NodeType FindSet(NodeType node) {
    if (node == parent[node]) {
      return node;
    }
    return parent[node] = FindSet(parent[node]);
  }

  void Hang(NodeType node, NodeType root, WeightType weight) {
    // hang node to root
    parent[node] = root;
    // std::cout << mass[root] << ' ' << mass[node] << ' ' << weight << std::endl;
    mass[root] += mass[node] + weight;
    // std::cout << "mass[0]: " << mass[0] << ' ' << std::endl;
  }

  void Union(const Edge& edge) {
    auto from = FindSet(edge.from);
    auto to = FindSet(edge.to);
    if (from == to) {
      mass[from] += edge.weight;
      return;
    }
    if (rank[from] >= rank[to]) {
      Hang(to, from, edge.weight);
      if (rank[from] == rank[to]) {
        ++rank[from];
      }
    } else {
      Hang(from, to, edge.weight);
    }
  }

 public:
  size_t size{};
  std::vector<size_t> parent{};
  std::vector<size_t> rank{};
  std::vector<size_t> mass{};
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  DSU dsu(n);
  for (size_t i = 0; i < m; ++i) {
    size_t operation{};
    std::cin >> operation;
    // std::cout <<"op: " << operation << std::endl;
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
        // std::cout << "root: " << root << std::endl;
        std::cout << dsu.mass[root] << std::endl;
        break;
      }
    }
  }
  return 0;
}
