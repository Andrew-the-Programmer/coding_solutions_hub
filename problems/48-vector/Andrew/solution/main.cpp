#include <iostream>
#include <cmath>

template <class T>
class Vector {
 public:
  T x;
  T y;

 public:
  Vector(const T& x, const T& y) : x(x), y(y) {
  }

  Vector() : Vector(0, 0) {
  }

  Vector(const Vector& begin, const Vector& end) : Vector(end - begin) {
  }

  double Length() {
    return std::sqrt(this->Dot(*this));
  }

  T Dot(const Vector& other) const {
    return x * other.x + y * other.y;
  }

  T Cross(const Vector& other) const {
    return x * other.y - y * other.x;
  }

  static T TriangleArea(const Vector& first, const Vector& second) {
    return std::abs(static_cast<double>(first.Cross(second))) / 2;
  }

  Vector operator+(const Vector& other) const {
    return {x + other.x, y + other.y};
  }

  Vector operator-() const {
    return {-x, -y};
  }

  Vector operator-(const Vector& other) const {
    return *this + (-other);
  }

  template <class IStream>
  void InputAsPoint(IStream& istream = std::cin) {
    istream >> x >> y;
  }

  template <class IStream>
  void InputAsBeginEnd(IStream& istream = std::cin) {
    Vector begin;
    Vector end;
    begin.InputAsPoint(istream);
    end.InputAsPoint(istream);
    *this = Vector(begin, end);
  }

  friend std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
    stream << vector.x << ' ' << vector.y;
    return stream;
  }

  friend std::istream& operator>>(std::istream& stream, Vector& vector) {
    vector.InputAsBeginEnd(stream);
    return stream;
  }
};

int main() {
  using T = double;
  using V = Vector<T>;

  V first;
  V second;

  std::cin >> first >> second;

  std::cout << std::fixed;

  std::cout << first.Length() << ' ' << second.Length() << std::endl;
  std::cout << first + second << std::endl;
  std::cout << first.Dot(second) << ' ' << first.Cross(second) << std::endl;
  std::cout << V::TriangleArea(first, second) << std::endl;
}
