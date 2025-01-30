#pragma once

#include <numeric>
#include <stdexcept>
#include <cinttypes>

#include <iostream>

class RationalDivisionByZero {};

class Rational {
public:
  using T = int64_t;

public:
  Rational (const T& numerator = 0, const T& denominator = 1); // NOLINT
  Rational (const Rational&);
  Rational& operator=(const Rational&);

protected:
  void TestDivByZero() const;
  void FixSigns();
  void Simplify();

public:
  const T& GetNumerator() const;
  T& GetNumerator();
  const T& GetDenominator() const;
  T& GetDenominator();

  void SetNumerator(const T&);
  void SetDenominator(const T&);

public:
  Rational Reciprocal() const;
  Rational OppositeSign() const;
  bool IsNegative() const;
  bool IsPositive() const;
  bool IsZero() const;
  bool IsInt() const;

public:
  friend Rational operator+(const Rational& r1, const Rational& r2);
  friend Rational operator-(const Rational& r1, const Rational& r2);
  friend Rational operator*(const Rational& r1, const Rational& r2);
  friend Rational operator/(const Rational& r1, const Rational& r2);

  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);
 
  Rational operator+() const;
  Rational operator-() const;

  Rational& operator++();
  Rational  operator++(int);
  Rational& operator--();
  Rational  operator--(int);

  friend bool operator==(const Rational& r1, const Rational& r2);
  friend bool operator< (const Rational& r1, const Rational& r2);
  friend bool operator<=(const Rational& r1, const Rational& r2);
  friend bool operator> (const Rational& r1, const Rational& r2);
  friend bool operator>=(const Rational& r1, const Rational& r2);

public:
  friend std::ostream& operator<<(std::ostream& stream, const Rational& r);
  friend std::istream& operator>>(std::istream& stream, Rational& r);

protected:
  T num_; // numerator
  T den_; // denominator
};
