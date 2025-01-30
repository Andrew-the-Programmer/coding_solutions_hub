#include "rational.h"

Rational::Rational (const T& numerator, const T& denominator) // NOLINT
: num_(numerator), den_(denominator) {Simplify();}
Rational::Rational (const Rational& other) : Rational(other.num_, other.den_) {}
Rational& Rational::operator=(const Rational& other) = default;

void Rational::TestDivByZero() const {
  if (den_ == 0) {
    throw RationalDivisionByZero{};
    // throw std::overflow_error("Division by zero in Rational");
  }
}
void Rational::FixSigns() {
  if (den_ < 0) {
    num_ *= -1;
    den_ *= -1;
  }
}
void Rational::Simplify() {
  TestDivByZero();
  FixSigns();
  Rational::T gcd = std::gcd(num_, den_);
  num_ /= gcd;
  den_ /= gcd;
}

const Rational::T& Rational::GetNumerator() const {
  return num_;
}
Rational::T& Rational::GetNumerator() {
  return num_;
}
const Rational::T& Rational::GetDenominator() const {
  return den_;
}
Rational::T& Rational::GetDenominator() {
  return den_;
}

void Rational::SetNumerator(const Rational::T& value) {
  num_ = value;
  Simplify();
}
void Rational::SetDenominator(const Rational::T& value) {
  den_ = value;
  Simplify();
}

Rational Rational::Reciprocal() const {
  return {den_, num_};
}
Rational Rational::OppositeSign() const {
  return {-num_, den_};
}

bool Rational::IsNegative() const {return num_ < 0;}
bool Rational::IsPositive() const {return num_ > 0;}
bool Rational::IsZero() const {return num_ == 0;}
bool Rational::IsInt() const {
  return den_ == 1;
}

Rational operator+(const Rational& r1, const Rational& r2) {
  return Rational {
    (r1.num_ * r2.den_ + r2.num_ * r1.den_), 
    (r1.den_ * r2.den_)
  };
}
Rational operator-(const Rational& r1, const Rational& r2) {
  return r1 + (-r2);
}
Rational operator*(const Rational& r1, const Rational& r2) {
  return Rational {
    (r1.num_ * r2.num_), 
    (r1.den_ * r2.den_)
  };
}
Rational operator/(const Rational& r1, const Rational& r2) {
  return r1 * r2.Reciprocal();
}

Rational& Rational::operator+=(const Rational& other) {
  num_ = num_ * other.den_ + other.num_ * den_;
  den_ *= other.den_;
  Simplify();
  return *this;
}
Rational& Rational::operator-=(const Rational& other) {
  return *this += other.OppositeSign();
}
Rational& Rational::operator*=(const Rational& other) {
  num_ *= other.num_;
  den_ *= other.den_;
  Simplify();
  return *this;
}
Rational& Rational::operator/=(const Rational& other) {
  return *this *= other.Reciprocal();
}

Rational Rational::operator+() const { return *this; }
Rational Rational::operator-() const { return this->OppositeSign(); }

Rational& Rational::operator++() {return *this += 1;}
Rational  Rational::operator++(int) {
  Rational old = *this;
  ++(*this);
  return old;
}
Rational& Rational::operator--() {return *this -= 1;}
Rational  Rational::operator--(int) {
  Rational old = *this;
  --(*this);
  return old;
}

bool operator<(const Rational& r1, const Rational& r2) {
  return r1.num_ * r2.den_ < r2.num_ * r1.den_;
}
bool operator==(const Rational& r1, const Rational& r2) {
  return !(r1 < r2) && !(r2 < r1);
  // return r1.num_ == r2.num_ && r1.den_ == r2.den_; //faster
}
bool operator<=(const Rational& r1, const Rational& r2) {
  return r1 < r2 || r1 == r2;
}
bool operator>(const Rational& r1, const Rational& r2) {
  return !(r1 <= r2);
}
bool operator>=(const Rational& r1, const Rational& r2) {
  return !(r1 < r2);
}

std::ostream& operator<<(std::ostream& stream, const Rational& r) {
  stream << r.GetNumerator();
  if (!r.IsInt()) {
    stream << "/" << r.GetDenominator();
  }
  return stream;
}
std::istream& operator>>(std::istream& stream, Rational& r) {
  stream >> r.GetNumerator();

  if (stream.peek() == '/') {
    stream.get();
    stream >> r.GetDenominator();
    r.Simplify();
  } else {
    r.GetDenominator() = 1;
  }

  return stream;
}
