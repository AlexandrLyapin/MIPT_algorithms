#ifndef RATIONAL
#define RATIONAL

#include <iostream>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  Rational();
  Rational(int x);  // NOLINT
  Rational(int numer, int denom);

  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int numer);
  void SetDenominator(int denom);
  friend Rational operator+(const Rational& left, const Rational& right);
  friend Rational operator-(const Rational& left, const Rational& right);
  friend Rational operator*(const Rational& left, const Rational& right);
  friend Rational operator/(const Rational& left, const Rational& right);
  friend bool operator==(const Rational& left, const Rational& right);
  friend bool operator!=(const Rational& left, const Rational& right);
  friend bool operator<(const Rational& left, const Rational& right);
  friend bool operator>(const Rational& left, const Rational& right);
  friend bool operator<=(const Rational& left, const Rational& right);
  friend bool operator>=(const Rational& left, const Rational& right);
  friend std::ostream& operator<<(std::ostream& out, const Rational& frac);
  friend std::istream& operator>>(std::istream& in, Rational& frac);
  Rational& operator=(const Rational& frac);
  Rational& operator+=(const Rational& frac);
  Rational& operator-=(const Rational& frac);
  Rational& operator*=(const Rational& frac);
  Rational& operator/=(const Rational& frac);
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
  Rational operator+() const;
  Rational operator-() const;
  ~Rational();

 private:
  void Simply();
  int64_t numerator_;
  int64_t denominator_;
};

#endif