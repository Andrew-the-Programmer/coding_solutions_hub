#include <functional>

template <class T, class U>
struct std::hash<std::pair<T, U>> {
  size_t operator()(const std::pair<T, U>& p) const {
    std::hash<T> h;
    return h(p.first) >> 1 | h(p.second);
  }
};

template <class T>
struct Point {};

template <class T>
struct std::hash<Point<T>> {
  size_t operator()(const Point<T>& p) const {
    return std::hash<std::pair<T, T>>{}(std::pair<T, T>(p.x, p.y));
  }
};
