#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using NodeType = size_t;

class DSU {
 public:
  explicit DSU(size_t size) : size(size), parent(size), rank(size), mass(size, 1) {
    for (NodeType i = 0; i < size; ++i) {
      MakeSet(i);
    }
  }

 public:
  void MakeSet(NodeType node) {
    parent[node] = node;
    rank[node] = 1;
  }

  NodeType FindSet(NodeType node) {
    if (node == parent[node]) {
      return node;
    }
    return parent[node] = FindSet(parent[node]);
  }

  void Hang(NodeType node, NodeType root) {
    // hang node to root
    parent[node] = root;
    mass[root] += mass[node];
  }

  bool Union(NodeType first, NodeType second) {
    auto first_root = FindSet(first);
    auto second_root = FindSet(second);
    if (first_root == second_root) {
      return false;
    }
    if (rank[first_root] < rank[second_root]) {
      Hang(first_root, second_root);
    } else if (rank[first_root] > rank[second_root]) {
      Hang(second_root, first_root);
    } else {
      Hang(first_root, second_root);
      ++rank[second_root];
    }
    return (mass[first_root] == size) || (mass[second_root] == size);
  }

 public:
  size_t size{};
  std::vector<size_t> parent{};
  std::vector<size_t> rank{};
  std::vector<size_t> mass{};
};

struct Edge {
  NodeType from;
  NodeType to;

  Edge() = default;
  Edge(NodeType from, NodeType to) : from(from), to(to) {
  }

  Edge Reverse() const {
    return {to, from};
  }
};

class Graph {
 public:
  explicit Graph(NodeType n) : dsu(n) {
  }
  DSU dsu;
};

bool CheckEdge(Graph& graph, const Edge& edge) {
  return graph.dsu.Union(edge.from, edge.to);
}

int main() {
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  Graph graph(n);
  for (size_t i = 0; i < m; i++) {
    NodeType from{};
    NodeType to{};
    std::cin >> from >> to;
    if (CheckEdge(graph, {from, to})) {
      std::cout << i + 1;
      break;
    }
  }
}
