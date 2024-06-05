// Copyright 2024 Andrew

#include <cstddef>
#include <iostream>
#include <optional>
#include <ostream>
#include <set>
#include <vector>
#include <queue>

template <class T>
struct Edge {
  T src;
  T dst;

  Edge() = default;

  template <class TT>
  friend std::ostream& operator<<(std::ostream& os, const Edge<TT>& edge) {
    os << edge.src << " -> " << edge.dst;
    return os;
  }

  template <class TT>
  friend std::istream& operator>>(std::istream& stream, Edge<TT>& edge) {
    std::cin >> edge.src >> edge.dst;
    return stream;
  }
};

struct Graph : public std::vector<std::set<size_t>> {
 protected:
  using Base = std::vector<std::set<size_t>>;
  using Base::Base;

 public:
  using VertexType = size_t;
  using EdgeType = Edge<size_t>;

 public:
  const auto& Neighbors(VertexType v) const {
    return this->at(v);
  }

  void AddNeighbor(VertexType src, VertexType dst) {
    this->at(src).emplace(dst);
  }

  void AddEdge(EdgeType edge) {
    AddNeighbor(edge.src, edge.dst);
    AddNeighbor(edge.dst, edge.src);
  }

 public:
  // using graph bipartiteness criterion
  // graph is bipartite <=> graph doesn't have cycles of odd length
  bool IsBipartite() const {
    std::vector<std::optional<int>> colors(this->size());
    // go through all connected components
    for (size_t start = 0; start < this->size(); ++start) {
      if (colors[start].has_value()) {
        continue;
      }
      std::queue<VertexType> q;
      q.push(start);
      colors[start] = 0;
      while (!q.empty()) {
        VertexType node = q.front();
        q.pop();
        for (auto&& neighbor : this->Neighbors(node)) {
          if (!colors[neighbor].has_value()) {
            colors[neighbor] = (colors[node].value() + 1) % 2;
            q.push(neighbor);
            continue;
          }
          if (colors[neighbor] == colors[node]) {  // cycle of odd length
            return false;
          }
        }
      }
    }
    return true;
  }
};

void Solution(const Graph& graph) {
  std::cout << (graph.IsBipartite() ? "YES" : "NO") << std::endl;
}

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;

  Graph graph(n + 1);
  for (size_t i = 0; i < m; ++i) {
    Edge<size_t> edge;
    std::cin >> edge;
    graph.AddEdge(edge);
  }

  Solution(graph);
}
