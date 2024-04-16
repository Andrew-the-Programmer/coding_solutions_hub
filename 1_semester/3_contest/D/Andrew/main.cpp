#include <iostream>

size_t Solution(size_t m, size_t n) {
  size_t dp[60][20]{};

  for (size_t i = 1; i <= m; ++i) {
    for (size_t j = 1; j <= n; ++j) {
      if (i < 2 || j < 2) {
        dp[i][j] = 1;
        continue;
      }
      size_t sum = 0;
      for (size_t k = 1; k < i; ++k) {
        sum += dp[i - k][j - 1];
      }
      dp[i][j] = dp[i][j - 1] + 2 * sum;
    }
  }

  return dp[m][n];
}

int main() {
  size_t m = 0;
  size_t n = 0;
  std::cin >> m >> n;
  std::cout << Solution(m, n);
}