// Copyright 2024 Andrew

#include <iostream>
#include <vector>

template <class T>
class RSQ {
 public:
  explicit RSQ(const std::vector<T>& vec) : prefix_sums(vec.size() + 1) {
    prefix_sums[0] = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
      prefix_sums[i + 1] = prefix_sums[i] + vec[i];
    }
  }

  T Get(size_t l, size_t r) {
    return prefix_sums[r] - prefix_sums[l];
  }

 public:
  std::vector<T> prefix_sums;
};

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<size_t> nums(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  RSQ rsq(nums);
  size_t k = 0;
  std::cin >> k;
  for (size_t i = 0; i < k; ++i) {
    size_t l = 0;
    size_t r = 0;
    std::cin >> l >> r;
    std::cout << rsq.Get(l - 1, r) << ' ';
  }
  std::cout << '\n';
  return 0;
}
