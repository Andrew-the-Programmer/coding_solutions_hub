#pragma once

// usefull functions

#include <iostream>

template <class T>
T Squared(const T& value) {
  return value * value;
}

template <class... T>
void Output(const T&... args) {
  ((std::cout << args << ' '), ...);
  std::cout << '\n';
}

template <class... T>
void Input(T&... args) {
  ((std::cin >> args), ...);
}

template <class T, class IStream = std::istream>
T InputResult(IStream& stream = std::cin) {
  T value;
  stream >> value;
  return value;
}
