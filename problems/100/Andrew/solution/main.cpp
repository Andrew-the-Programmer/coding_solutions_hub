#include <iostream>
#include <limits>
#include <vector>

void FordWarshell(std::vector<std::vector<int64_t>>& matrix) {
  for (size_t i{}; i < matrix.size(); i++) {
    for (size_t j{}; j < matrix.size(); j++) {
      for (size_t y{}; y < matrix.size(); y++) {
        matrix[j][y] = std::min(matrix[j][y], matrix[j][i] + matrix[i][y]);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  int64_t n{};
  std::cin >> n;
  std::vector<std::vector<int64_t>> graph_matrix(n, std::vector<int64_t>(n, 0));
  for (int64_t i{}; i < n; i++) {
    for (int64_t j{}; j < n; j++) {
      int64_t weight{};
      std::cin >> weight;
      graph_matrix[i][j] = weight;
    }
  }
  FordWarshell(graph_matrix);
  for (int64_t i{}; i < n; i++) {
    for (int64_t j{}; j < n; j++) {
      std::cout << graph_matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  return 0;
}