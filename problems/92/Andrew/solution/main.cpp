#include <optional>
#include <unordered_set>
#include <vector>
#include <iostream>

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

  friend auto& operator<<(std::ostream& out, const Edge& edge) {
    return out << edge.from << ' ' << edge.to << ' ' << edge.weight;
  }
};

class Graph {
 public:
  using AdjListT = std::vector<std::vector<Edge>>;
  class DSU {
   public:
    explicit DSU(size_t size) : size(size), sets_count(size), parent(size), rank(size, 0), mass(size, 0) {
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
      mass[root] += mass[node] + weight;
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
      --sets_count;
    }

    size_t CountSets() const {
      return sets_count;
    }

    bool InSameSet(NodeType first, NodeType second) {
      return FindSet(first) == FindSet(second);
    }

    auto GetSets() {
      std::unordered_set<NodeType> sets;
      for (NodeType i = 0; i < size; ++i) {
        sets.insert(FindSet(i));
      }
      return sets;
    }

   public:
    size_t size{};
    size_t sets_count{};
    std::vector<NodeType> parent{};
    std::vector<size_t> rank{};
    std::vector<size_t> mass{};
  };

 public:
  explicit Graph(size_t n) : nodes_count(n), components(n) {
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

 public:
  size_t nodes_count = 0;
  std::vector<Edge> edges;
  mutable DSU components;
};

size_t BoruvkasAlgorithm(const Graph& graph) {
  auto n = graph.CountNodes();
  auto& components = graph.components;
  while (components.CountSets() > 1) {
    std::vector<std::optional<Edge>> cheapest(n);
    for (auto& edge : graph.GetAllEdges()) {
      if (components.InSameSet(edge.from, edge.to)) {
        continue;
      }
      auto root1 = components.FindSet(edge.from);
      auto root2 = components.FindSet(edge.to);

      auto set_cheapest = [&](NodeType root, Edge edge) {
        auto cur_cheapest_edge = cheapest[root];
        if (!cur_cheapest_edge || cur_cheapest_edge->weight > edge.weight) {
          cheapest[root] = edge;
        }
      };
      set_cheapest(root1, edge);
      set_cheapest(root2, edge);
    }
    for (NodeType node = 0; node < n; ++node) {
      auto cheapest_edge = cheapest[node];
      if (!cheapest_edge) {
        continue;
      }
      if (components.InSameSet(cheapest_edge->from, cheapest_edge->to)) {
        continue;
      }
      components.Union(*cheapest_edge);
    }
  }

  return components.mass[components.FindSet(0)];
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

  auto min_weight = BoruvkasAlgorithm(graph);
  std::cout << min_weight << '\n';
  return 0;
}
