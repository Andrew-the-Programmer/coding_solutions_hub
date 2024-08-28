#include <iostream>
#include <iterator>
#include <optional>
#include <vector>
#include <algorithm>

using NodeType = size_t;

// Edge: oriented, not weighted
struct Edge {
  NodeType from;
  NodeType to;

  Edge() = default;
  Edge(NodeType from, NodeType to) : from(from), to(to) {
  }

  friend auto& operator<<(std::ostream& stream, const Edge& edge) {
    stream << edge.from << ' ' << edge.to;
    return stream;
  }

  friend std::istream& operator>>(std::istream& stream, Edge& edge) {
    stream >> edge.from >> edge.to;
    return stream;
  }
};

// Graph: oriented
class GraphO {
  using AdjListT = std::vector<std::vector<Edge>>;

 public:
  explicit GraphO(size_t n) : adj_list_(n) {
  }

  void AddEdge(const Edge& edge) {
    adj_list_[edge.from].emplace_back(edge);
  }

  size_t CountNodes() const {
    return adj_list_.size();
  }

  auto&& GetEdges(NodeType node) const {
    return adj_list_[node];
  }

 protected:
  AdjListT adj_list_;
};

using E = Edge;
using G = GraphO;

enum class Color { WHITE, GREY, BLACK };

auto DfsRecursive(const G& graph, std::vector<Color>& colors, std::vector<NodeType>& loop,
                  NodeType cur) -> std::optional<NodeType> {
  loop.push_back(cur);
  colors[cur] = Color::GREY;
  for (auto& edge : graph.GetEdges(cur)) {
    auto next = edge.to;
    if (colors[next] == Color::GREY) {
      // next was visited -> found cycle
      return next;
    }
    if (colors[next] == Color::WHITE) {
      // next was not yet visited
      auto dfs = DfsRecursive(graph, colors, loop, next);
      if (dfs.has_value()) {
        // dfs found cycle
        return dfs;
      }
    }
  }
  colors[cur] = Color::BLACK;
  loop.pop_back();
  return {};
}

template <std::forward_iterator Iter>
void OutputLoop(Iter begin, Iter end) {
  std::cout << "YES\n";
  for (auto i = begin; i != end; ++i) {
    std::cout << *i + 1 << ' ';
  }
}

void FindLoop(const G& graph) {
  size_t n = graph.CountNodes();
  std::vector colors(n, Color::WHITE);
  std::vector<NodeType> loop;
  loop.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    if (colors[i] == Color::BLACK) {
      continue;
    }
    loop.resize(0);
    auto dfs = DfsRecursive(graph, colors, loop, i);
    if (dfs.has_value()) {
      auto begin = std::find(loop.begin(), loop.end(), dfs.value());
      OutputLoop(begin, loop.end());
      return;
    }
  }
  std::cout << "NO" << std::endl;
}

int main() {
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  G graph(n);
  for (size_t i = 0; i < m; ++i) {
    NodeType from{};
    NodeType to{};
    std::cin >> from >> to;
    --from;
    --to;
    graph.AddEdge({from, to});
  }
  FindLoop(graph);
  return 0;
}
