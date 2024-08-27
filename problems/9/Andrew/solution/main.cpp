#include <iostream>

size_t GetCypheredMsg(char* cyphered_msg) {
  for (size_t i = 0;; ++i) {
    char value = static_cast<char>(std::getchar());
    if (value == '#') {
      return i;
    }
    cyphered_msg[i] = value;
  }
}

size_t RealIndex(size_t false_index, size_t size) {
  if (false_index % 2 == 0) {
    return false_index / 2;
  }
  return size - 1 - false_index / 2;
}

void DecypherMsg(char* cyphered_msg, char* real_msg, size_t real_size) {
  for (size_t false_index = 0; false_index < real_size; ++false_index) {
    real_msg[RealIndex(false_index, real_size)] = cyphered_msg[false_index];
  }
}

int main() {
  constexpr size_t kMaxSize = 1e5;
  size_t real_size = 0;

  char cyphered_msg[kMaxSize];
  char real_msg[kMaxSize];

  real_size = GetCypheredMsg(cyphered_msg);

  DecypherMsg(cyphered_msg, real_msg, real_size);

  std::cout << real_msg;
}