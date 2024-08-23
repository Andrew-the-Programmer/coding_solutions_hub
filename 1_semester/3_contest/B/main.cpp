#include <iostream>

size_t Solution(size_t n, size_t* arr) {
  if (n == 0) {
    return 1;
  }
  if (n == 1) {
    return 3;
  }
  if (arr[n] == 0) {
    arr[n] = 2 * (Solution(n - 1, arr) + Solution(n - 2, arr));
  }
  return arr[n];
}

int main() {
  size_t n = 0;
  std::cin >> n;
  size_t arr[100]{};
  std::cout << Solution(n, arr);
  return 0;
}
