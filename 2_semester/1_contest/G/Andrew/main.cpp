#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include <optional>

template <class T, class IStream = std::istream>
void Input(T& value, IStream& istream = std::cin) {
  istream >> value;
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

  friend auto& operator>>(std::istream& stream, Vector& vector) {
    using V = Vector<T>;
    using P = typename V::PointType;
    vector = V(InputResult<P>());
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
  using VectorType = Vector<T>;

  auto GetSegmentVector(size_t index) const {
    if (this->size() < 2) {
      throw std::logic_error("Polygon doesn't have segments");
    }
    if (index >= this->size()) {
      throw std::out_of_range("Index out of range");
    }
    if (index == this->size() - 1) {
      return VectorType(this->back(), this->front());
    }
    return VectorType(this->at(index), this->at(index + 1));
  }

  auto GetSegmentCross(size_t index) const {
    size_t begin = index;
    size_t end = (index + 1) % this->size();
    return GetSegmentVector(begin).Cross(GetSegmentVector(end));
  }

  bool IsConvex() const {
    if (this->size() < 2) {
      return true;
    }
    std::optional<bool> angles_are_positive;
    // check if all angles have the same sign
    for (size_t i = 0; i < this->size(); ++i) {
      auto curr_cross = GetSegmentCross(i);
      if (curr_cross == 0) {
        continue;
      }
      bool curr_angle_is_positive = curr_cross > 0;
      if (angles_are_positive.has_value()) {
        if (angles_are_positive.value() != curr_angle_is_positive) {
          return false;
        }
      } else {
        angles_are_positive = curr_angle_is_positive;
      }
    }
    return true;
  }
};

void Solution() {
  using T = int64_t;

  Polygon<T> polygon;
  Input(polygon, InputResult<size_t>());

  if (polygon.IsConvex()) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}

int main() {
  std::cout << std::fixed << std::setprecision(1);

  // std::cout << static_cast<T>(1e18) << std::endl;
  // std::cout << static_cast<long double>(1e18) + 0.1 << std::endl;
  // std::cout << (1e18 + 0.1) << std::endl;

  Solution();
}
