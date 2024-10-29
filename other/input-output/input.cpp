#include <iostream>
#include <vector>

template <class T, class IStream = std::istream>
void Input(T& value, IStream& istream = std::cin) {
  istream >> value;
}

template <std::forward_iterator Iter>
void Input(Iter begin, Iter end) {
  for (auto i = begin; i != end; ++i) {
    std::cin >> *i;
  }
}

template <class T, class IStream = std::istream>
void Input(T begin, T end, IStream& istream = std::cin) {
  for (auto i = begin; i != end; ++i) {
    Input(*i, istream);
  }
}

template <class... T>
void Input(T&... args) {
  (Input(args, std::cin), ...);
}

template <class T, class IStream = std::istream>
T InputResult(IStream& istream = std::cin) {
  T value;
  Input(value, istream);
  return value;
}

template <class T, class IStream = std::istream>
void Input(std::vector<T>& vector, size_t size, IStream& istream = std::cin) {
  vector.reserve(size + vector.size());
  for (size_t i = 0; i < size; ++i) {
    vector.emplace_back(InputResult<T>(istream));
  }
}

template <class T, class IStream = std::istream>
void Input(std::vector<T>& vector, IStream& istream = std::cin) {
  T value;
  while (std::cin >> value) {
    vector.emplace_back(value);
  }
}

template <class T, class IStream = std::istream>
auto GetVector(IStream& istream = std::cin) {
  return InputResult<std::vector<T>>(istream);
}
