#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
struct Edge {
  int64_t to;
  int64_t wght;
  Edge() = default;
  Edge(const int64_t& to, const int64_t& weight) : to(to), wght(weight) {
  }
};
class Graph {
 public:
  explicit Graph(int64_t vert_amoun, const int64_t edge_amoun_in_path, const int64_t bgvex, const int64_t endvex)
      : vert_amoun_(vert_amoun), edge_amoun_in_path_(edge_amoun_in_path), bgvex_(bgvex), endvex_(endvex) {
    edges_.resize(vert_amoun_);
    dist_.resize(edge_amoun_in_path + 1);
    for (int64_t i = 0; i <= edge_amoun_in_path; ++i) {
      dist_[i].resize(vert_amoun_, k_max_wght);
    }
  }
  void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight);
  void PrintMinDist();
  const int64_t k_max_wght = 1000000000;
  int64_t vert_amoun_;
  int64_t edge_amoun_in_path_;
  int64_t bgvex_;
  int64_t endvex_;
  std::vector<std::vector<Edge>> edges_;
  std::vector<std::vector<int64_t>> dist_;
  bool Relax(int64_t order, int64_t from, const Edge& edge);
  void BellmanFord();
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
  edges_[first_vert].emplace_back(second_vert, weight);
}
bool Graph::Relax(const int64_t order, const int64_t from, const Edge& edge) {
  if (dist_[order + 1][edge.to] > dist_[order][from] + edge.wght) {
    dist_[order + 1][edge.to] = dist_[order][from] + edge.wght;
    return true;
  }
  return false;
}
void Graph::BellmanFord() {
  dist_[0][bgvex_] = 0;
  std::vector<std::queue<int64_t>> queues;
  queues.resize(edge_amoun_in_path_ + 2);
  queues[0].push(bgvex_);
  for (int64_t k = 0; (!queues[k].empty() && k < edge_amoun_in_path_); k++) {
    bool is_change = false;
    while (!queues[k].empty()) {
      const auto new_vert = queues[k].front();
      queues[k].pop();
      for (auto& edge : edges_[new_vert]) {
        if (Relax(k, new_vert, edge)) {
          queues[k + 1].push(edge.to);
          is_change = true;
        }
      }
    }
    if (!is_change) {
      break;
    }
  }
}
void Graph::PrintMinDist() {
  BellmanFord();
  int64_t min_weight = k_max_wght;
  for (int64_t i = 0; i <= edge_amoun_in_path_; i++) {
    if (dist_[i][endvex_] < min_weight) {
      min_weight = dist_[i][endvex_];
    }
  }
  if (min_weight == k_max_wght) {
    min_weight = -1;
  }
  std::cout << min_weight;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  int64_t vert_amoun{};
  int64_t edge_amoun{};
  int64_t edge_amoun_in_path{};
  int64_t bgv{};
  int64_t endv{};
  std::cin >> vert_amoun >> edge_amoun;
  std::cin >> edge_amoun_in_path >> bgv >> endv;
  Graph graph(vert_amoun, edge_amoun_in_path, bgv - 1, endv - 1);
  int64_t first_vert{};
  int64_t second_vert{};
  int64_t weight{};
  for (int64_t i = 0; i < edge_amoun; i++) {
    std::cin >> first_vert >> second_vert >> weight;
    graph.PushEdge(first_vert - 1, second_vert - 1, weight);
  }
  graph.PrintMinDist();
  return 0;
}