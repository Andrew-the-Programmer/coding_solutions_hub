#include <iostream>

template <class T>
auto Min(const T& value) {
  return value;
}

template <class T, class U, class... Tail>
auto Min(const T& t, const U& u, const Tail&... tail) {
  return Min((u < t ? u : t), tail...);
}

size_t Solution(size_t begin, size_t end) {
  auto dp = new size_t[end + 1];

  dp[end] = 0;

  for (size_t i = end - 1; i >= begin; --i) {
    if (i * 2 > end) {
      dp[i] = dp[i + 1] + 1;
    } else if (i * 3 > end) {
      dp[i] = Min(dp[i + 1], dp[i * 2]) + 1;
    } else {
      dp[i] = Min(dp[i + 1], dp[i * 2], dp[i * 3]) + 1;
    }
  }

  size_t result = dp[begin];
  delete[] dp;
  return result;
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::cout << Solution(1, n);
}