#include <iostream>
#include <vector>
#include <cstdint>

// with size_t ML on test 30 💀
// with uint8_t ML on test 18 💀💀💀 (int overflow)
using NodeType = uint16_t;

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

// Graph: oriented
class Graph {
  using AdjListT = std::vector<std::vector<Edge>>;

 public:
  explicit Graph(size_t n) : adj_list_(n) {
  }

  void AddEdge(const Edge &edge) {
    adj_list_[edge.from].emplace_back(edge);
  }

  size_t CountNodes() const {
    return adj_list_.size();
  }

  auto &&GetEdges(NodeType node) const {
    return adj_list_[node];
  }

 protected:
  AdjListT adj_list_;
};

enum class Color { WHITE, GRAY, BLACK };

bool FindLoop(const Graph &graph, NodeType cur, std::vector<Color> &colors) {
  colors[cur] = Color::GRAY;
  for (auto &edge : graph.GetEdges(cur)) {
    auto neighbor = edge.to;
    if (colors[neighbor] == Color::GRAY) {
      return true;
    }
    if (colors[neighbor] == Color::WHITE && FindLoop(graph, neighbor, colors)) {
      return true;
    }
  }
  colors[cur] = Color::BLACK;
  return false;
}

bool IsMono(const std::vector<std::vector<char>> &arrows) {
  auto n = arrows.size() + 1;
  Graph graph(n);
  for (NodeType i = 0; i < n - 1; ++i) {
    for (NodeType j = 0; j < n - i - 1; ++j) {
      NodeType from = i;
      NodeType to = i + j + 1;
      if (arrows[i][j] == 'R') {
        graph.AddEdge({from, to});
      } else {
        graph.AddEdge({to, from});
      }
    }
  }
  std::vector<Color> colors(n, Color::WHITE);
  for (NodeType start = 0; start < n; ++start) {
    if (colors[start] != Color::WHITE) {
      continue;
    }
    if (FindLoop(graph, start, colors)) {
      return false;
    }
  }
  return true;
}

int main() {
  size_t n{};
  std::cin >> n;
  std::vector<std::vector<char>> arrows(n - 1);
  for (size_t i = 0; i < n - 1; ++i) {
    arrows[i].resize(n - i - 1);
    for (size_t j = 0; j < n - i - 1; ++j) {
      std::cin >> arrows[i][j];
    }
  }
  std::cout << (IsMono(arrows) ? "YES" : "NO") << std::endl;
  return 0;
}
