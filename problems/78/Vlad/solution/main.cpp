#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
struct Edge {
  int64_t vertex_{};
  int64_t order_{};
  Edge(const int64_t &vertex, const int64_t &order) : vertex_(vertex), order_(order) {
  }
  Edge() = default;
};
struct EdgeBridge {
  int64_t from_{};
  int64_t to_{};
  int64_t order_{};
  EdgeBridge(const int64_t &from, const int64_t &to, const int64_t &order) : from_(from), to_(to), order_(order) {
  }
  friend bool operator<(const EdgeBridge &first, const EdgeBridge &second) {
    return ((first.from_ < second.from_) || ((first.from_ == second.from_) && (first.to_ < second.to_)) ||
            ((first.from_ == second.from_) && (first.to_ == second.to_) && (first.order_ < second.order_)));
  }
  EdgeBridge() = default;
};
class Graph {
 public:
  explicit Graph(const int64_t &new_quantity_vert, const int64_t &quantity_edges)
      : quantity_vert_(new_quantity_vert), quantity_edges_(quantity_edges) {
    edges_.resize(quantity_vert_ + 1);
    colors_.resize(quantity_vert_ + 1, 0);
    time_in_.resize(quantity_vert_ + 1, -1);
    time_up_.resize(quantity_vert_ + 1, -1);
    bridges_.resize(quantity_edges + 1, 0);
  }
  void PushEdge(const int64_t &first_vert, const int64_t &second_vert, const int64_t &order) {
    multiplies_edges_.emplace_back(std::min(first_vert, second_vert), std::max(first_vert, second_vert), order);
  }
  void PushCorrectEdge(const int64_t &first_vert, const int64_t &second_vert, const int64_t &order) {
    edges_[first_vert].emplace_back(second_vert, order);
    edges_[second_vert].emplace_back(first_vert, order);
  }
  void DeleteMultipliesEdges() {
    std::sort(multiplies_edges_.begin(), multiplies_edges_.end());
    for (int64_t i = 0; i < quantity_edges_;) {
      int64_t j = i + 1;
      while ((j < quantity_edges_) && (multiplies_edges_[i].from_ == multiplies_edges_[j].from_) &&
             (multiplies_edges_[i].to_ == multiplies_edges_[j].to_)) {
        ++j;
      }
      if (i + 1 == j) {
        PushCorrectEdge(multiplies_edges_[i].from_, multiplies_edges_[i].to_, multiplies_edges_[i].order_);
      }
      i = j;
    }
  }
  void PrintBridges() {
    DeleteMultipliesEdges();
    DFS();
    std::cout << size_bridges_ << std::endl;
    for (int64_t i = 1; i <= quantity_edges_; i++) {
      if (bridges_[i] == 1) {
        std::cout << i << std::endl;
      }
    }
  }

 private:
  std::vector<std::vector<Edge>> edges_{};
  int64_t quantity_vert_{};
  int64_t quantity_edges_{};
  int64_t size_bridges_{};
  std::vector<int64_t> colors_{};
  std::vector<int64_t> time_in_{};
  std::vector<int64_t> time_up_{};
  std::vector<EdgeBridge> multiplies_edges_{};
  std::vector<int64_t> bridges_{};
  int64_t time_{};
  void DFS() {
    for (int64_t i = 1; i <= quantity_vert_; ++i) {
      if (colors_[i] == 0) {
        DfsVisit(0, i);
      }
    }
  }
  void DfsVisit(int64_t parent, int64_t begin_vertex) {
    colors_[begin_vertex] = 1;
    time_in_[begin_vertex] = time_;
    time_up_[begin_vertex] = time_;
    time_++;
    for (auto neighbor : edges_[begin_vertex]) {
      if ((colors_[neighbor.vertex_] == 1) && (parent != neighbor.vertex_)) {
        time_up_[begin_vertex] = std::min(time_up_[begin_vertex], time_in_[neighbor.vertex_]);
      }
      if (colors_[neighbor.vertex_] == 0) {
        DfsVisit(begin_vertex, neighbor.vertex_);
        time_up_[begin_vertex] = std::min(time_up_[begin_vertex], time_up_[neighbor.vertex_]);
        if (time_in_[begin_vertex] < time_up_[neighbor.vertex_]) {
          bridges_[neighbor.order_] = 1;
          size_bridges_++;
        }
      }
    }
    colors_[begin_vertex] = 2;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes, quantity_edges);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  for (int64_t i = 1; i <= quantity_edges; i++) {
    std::cin >> first_vert >> second_vert;
    graph.PushEdge(first_vert, second_vert, i);
  }
  graph.PrintBridges();
  return 0;
}