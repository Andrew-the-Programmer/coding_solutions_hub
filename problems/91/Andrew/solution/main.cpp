#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>
#include <memory>

using NodeType = size_t;
using WeightType = size_t;

struct Edge {
  NodeType from;
  NodeType to;
  WeightType weight;

  Edge() = default;
  Edge(NodeType from, NodeType to, WeightType weight) : from(from), to(to), weight(weight) {
  }

  Edge Reverse() const {
    return {to, from, weight};
  }
};

// Graph: not oriented
class Graph {
  using AdjListT = std::vector<std::vector<Edge>>;
  using EdgesListT = std::vector<Edge>;

 public:
  explicit Graph(size_t n) : nodes_count(n) {
  }

  void AddEdge(const Edge& edge) {
    edges.emplace_back(edge);
  }

  size_t CountNodes() const {
    return nodes_count;
  }

  auto&& GetAllEdges() const {
    return edges;
  }

 protected:
  size_t nodes_count = 0;
  std::vector<Edge> edges;
};

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

  bool InSameSet(NodeType first, NodeType second) {
    return FindSet(first) == FindSet(second);
  }

 public:
  size_t size{};
  std::vector<size_t> parent{};
  std::vector<size_t> rank{};
  std::vector<size_t> mass{};
};

size_t KruskalAlgorithm(const Graph& graph) {
  auto n = graph.CountNodes();
  auto cmp = [](const Edge& first, const Edge& second) { return first.weight > second.weight; };
  auto& edges = graph.GetAllEdges();
  std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> queue(edges.begin(), edges.end(), cmp);
  DSU dsu(n);

  WeightType total_weight = 0;

  while (!queue.empty()) {
    auto min_edge = queue.top();
    queue.pop();
    if (dsu.InSameSet(min_edge.from, min_edge.to)) {
      continue;
    }
    total_weight += min_edge.weight;
    dsu.Union(min_edge.from, min_edge.to);
  }
  return total_weight;
}

void SetIostream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
}

int main() {
  SetIostream();

  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  Graph graph(n);
  for (size_t i = 0; i < m; i++) {
    NodeType from{};
    NodeType to{};
    WeightType weight{};
    std::cin >> from >> to >> weight;
    --from;
    --to;
    graph.AddEdge({from, to, weight});
  }

  auto min_weight = KruskalAlgorithm(graph);
  std::cout << min_weight << '\n';
  return 0;
}
