// Copyright 2024 Vlad

#include <iostream>
#include <queue>
#include <vector>
#include <set>

struct SNM {
  int *data{};
  size_t size{};
  SNM() = default;
  ~SNM() {
    delete[] data;
  };
  SNM(int size) {  // NOLINT
    data = new int[size];
    for (int i = 0; i < size; ++i) {
      data[i] = i;
    }
  }
  int Find(int n) {
    if (n == data[n]) {
      return n;
    }
    return (Find(data[n]));
  }
  int Join(int a, int b) {
    if (Find(a) == Find(b)) {
      return 0;
    };
    data[Find(a)] = Find(b);
    return 1;
  }
};

int main() {
  int n{};
  int a{};
  std::cin >> n;
  SNM snm(n);
  int count = n;
  for (int i = 0; i < n; ++i) {
    std::cin >> a;
    count -= snm.Join(i, a - 1);
  }
  std::cout << count;
  return 0;
}
