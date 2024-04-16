#include <iostream>

template <class T>
void Output(const T& n) {
  std::cout << n << ' ';
}

template <class T>
void OutputRange(const T& begin, const T& end) {
  for (T i = begin; i != end; ++i) {
    Output(i);
  }
}

void Clean(int);
void Fill(int);

void Clean(int n) {
  if (n <= 2) {
    OutputRange(-n, 0);
    return;
  }
  Clean(n - 2);
  Output(-n);
  Fill(n - 2);
  Clean(n - 1);
}

void Fill(int n) {
  if (n <= 2) {
    OutputRange(1, n + 1);
    return;
  }
  Fill(n - 1);
  Clean(n - 2);
  Output(n);
  Fill(n - 2);
}

int main() {
  int n = 0;
  std::cin >> n;
  Fill(n);
}