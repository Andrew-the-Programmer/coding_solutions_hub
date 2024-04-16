#include <iostream>
#include <cmath>

size_t Solution(size_t n) {
  size_t dp[10][21]{};  // dp[m][n] = amount of numbers with length n, starting with digit m.

  for (size_t length = 0; length < 2; ++length) {
    for (size_t digit = 0; digit < 10; ++digit) {
      dp[digit][length] = length;
    }
  }

  for (size_t i = 2; i <= n; ++i) {
    dp[0][i] = dp[4][i - 1] + dp[6][i - 1];
    dp[1][i] = dp[6][i - 1] + dp[8][i - 1];
    dp[2][i] = dp[7][i - 1] + dp[9][i - 1];
    dp[3][i] = dp[4][i - 1] + dp[8][i - 1];
    dp[4][i] = dp[0][i - 1] + dp[3][i - 1] + dp[9][i - 1];
    dp[5][i] = 0;
    dp[6][i] = dp[0][i - 1] + dp[1][i - 1] + dp[7][i - 1];
    dp[7][i] = dp[2][i - 1] + dp[6][i - 1];
    dp[8][i] = dp[1][i - 1] + dp[3][i - 1];
    dp[9][i] = dp[2][i - 1] + dp[4][i - 1];
  }

  size_t result = 0;

  for (size_t digit = 0; digit < 10; ++digit) {
    if (digit != 0 && digit != 8) {
      result += dp[digit][n];
    }
  }

  return result;
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::cout << Solution(n);
}