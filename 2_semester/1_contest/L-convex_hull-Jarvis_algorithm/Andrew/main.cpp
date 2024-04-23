#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>

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

template <class T>
T InputResult() {
  T value;
  std::cin >> value;
  return value;
}

struct IOutputClass {
  virtual std::string ToString() const = 0;

  friend auto& operator<<(std::ostream& stream, const IOutputClass& value) {
    stream << value.ToString();
    return stream;
  }

  virtual ~IOutputClass() = default;
};

template <class T>
struct Vector;

template <class T>
struct Point : IOutputClass {
  using VectorType = Vector<T>;

  T x;
  T y;

  Point() = default;
  Point(const T& x, const T& y) : x(x), y(y) {
  }

  std::string ToString() const override {
    std::stringstream ss;
    ss << x << " " << y;
    return ss.str();
  }

  VectorType operator-(const Point& other) const {
    return {other, *this};
  }

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Point& other) const {
    return !(*this == other);
  }

  friend auto& operator>>(std::istream& stream, Point& point) {
    stream >> point.x >> point.y;
    return stream;
  }
};

template <class T>
struct Vector : IOutputClass {
  using PointType = Point<T>;

  T x;
  T y;

  Vector() = default;
  Vector(const T& x, const T& y) : x(x), y(y) {
  }
  Vector(const PointType& point) : Vector(point.x, point.y) {  // NOLINT
  }
  Vector(const PointType& begin, const PointType& end) : Vector(end.x - begin.x, end.y - begin.y) {
  }

  explicit operator PointType() const {
    return {x, y};
  }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "Vector(" << x << ", " << y << ")";
    return ss.str();
  }

  bool IsZero() const {
    return x == 0 && y == 0;
  }

  auto SquaredLength() const {
    return this->Dot(*this);
  }

  double Length() const {
    return std::sqrt(SquaredLength());
  }

  auto Dot(const Vector& other) const {
    return x * other.x + y * other.y;
  }

  auto Cross(const Vector& other) const {
    return x * other.y - y * other.x;
  }

  Vector& operator+=(const Vector& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector operator+(const Vector& other) const {
    auto result = *this;
    result += other;
    return result;
  }

  Vector& operator-=(const Vector& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vector operator-(const Vector& other) const {
    auto result = *this;
    result -= other;
    return result;
  }

  Vector operator-() const {
    return {-x, -y};
  }

  bool operator==(const Vector& other) const {
    return x == other.x && y == other.y;
  }

  // TODO:
  friend auto& operator>>(std::istream& stream, Vector& vector) {
    stream >> vector.x >> vector.y;
    return stream;
  }

  bool LongerThan(const Vector& other) const {
    return SquaredLength() > other.SquaredLength();
  }
};

template <class T>
struct Polygon : std::vector<Point<T>>, IOutputClass {
  using Base = std::vector<Point<T>>;

  using Base::Base;
  using typename Base::value_type;

  std::string ToString() const override {
    std::stringstream ss;
    for (size_t i = 0; i < this->size(); ++i) {
      if (i != 0) {
        ss << '\n';
      }
      ss << this->at(i);
    }
    return ss.str();
  }

  void Input(size_t size) {
    this->reserve(this->size() + size * 3);
    value_type value;
    for (size_t i = 0; i < size; ++i) {
      std::cin >> value;
      this->emplace_back(value);
      this->emplace_back(value);
      this->emplace_back(value);
    }
  }
  void Input() {
    this->resize(0);
    value_type value;
    while (std::cin >> value) {
      this->emplace_back(value);
    }
  }

  auto Surface() {
    using S = double;
    S surface = 0;
    for (size_t i = 0; i < this->size() - 1; ++i) {
      surface += static_cast<S>(Vector<T>(this->at(i)).Cross(this->at(i + 1)));
    }
    surface += static_cast<S>(Vector<T>(this->back()).Cross(this->front()));
    return std::abs(surface) / 2;
  }
};

template <class T>
const Point<T>& FindMinPoint(const Polygon<T>& polygon) {
  auto min = polygon.begin();
  for (auto it = polygon.begin(); it != polygon.end(); ++it) {
    if (it->x < min->x || (it->x == min->x && it->y < min->y)) {
      min = it;
    }
  }
  return *min;
}

template <class T>
void SortPoligonByAngles(Polygon<T>& polygon) {
  const Point<T> min_point = FindMinPoint(polygon);
  // std::cout << "min_point = " << min_point << std::endl;
  auto cmp_greater = [&min_point](const Point<T>& a, const Point<T>& b) -> bool {
    Vector<T> ma(min_point, a);
    Vector<T> mb(min_point, b);
    auto area = ma.Cross(mb);
    if (area != 0) {
      return area < 0;
    }
    return mb.LongerThan(ma);
  };

  std::sort(polygon.begin(), polygon.end(), cmp_greater);
}

template <class T>
Polygon<T> FindConvexHullGrahamAlgorithm(Polygon<T>& polygon) {
  Polygon<T> result;
  SortPoligonByAngles(polygon);
  for (size_t cur_point_index = 0; cur_point_index < polygon.size(); ++cur_point_index) {
    auto curr = polygon.at(cur_point_index);

    while (true) {
      if (result.size() <= 1) {
        if (result.size() == 1 && result.front() == curr) {
          break;
        }
        result.emplace_back(curr);
        break;
      }

      auto p1 = result[result.size() - 1];
      auto p2 = result[result.size() - 2];
      auto v1 = Vector<T>(p2, p1);
      auto v2 = Vector<T>(p1, curr);

      if (v1.Cross(v2) >= 0) {
        result.pop_back();
        continue;
      }

      result.emplace_back(curr);
      break;
    }
  }
  return result;
}

int main() {
  using T = int64_t;

  // Polygon<int> polygon{{1, 2}, {2, 1}, {-2, 1}, {0, 0}};
  std::cout << std::fixed << std::setprecision(1);

  Polygon<T> polygon;
  polygon.Input(InputResult<size_t>());

  // std::cout << "sorted:\n";
  // auto copy = polygon;
  // SortPoligonByAngles(copy);
  // std::cout << copy << std::endl;

  // std::cout << "answer:\n";
  auto hull = FindConvexHullGrahamAlgorithm(polygon);
  std::cout << hull.size() << '\n' << hull << '\n' << hull.Surface() << '\n';
}
