#include "rational.h"

#include <iostream>
#include <stdexcept>
#include <numeric>
#include <cstring>

void FractionReduction(int64_t& a, int64_t& b) {
  int64_t numer = a;
  int64_t denom = b;
  if (numer == denom) {
    a = 1;
    b = 1;
    return;
  }
  if (numer == -denom) {
    a = -1;
    b = 1;
    return;
  }
  if (numer == 0) {
    b = 1;
    return;
  }
  int64_t factor = std::gcd(numer, denom);
  if (factor != 1) {
    numer /= factor;
    denom /= factor;
  }
  if (numer < 0 && denom < 0) {
    numer = -numer;
    denom = -denom;
  } else {
    if (numer > 0 && denom < 0) {
      denom = -denom;
      numer = -numer;
    }
  }
  a = numer;
  b = denom;
}

Rational::Rational() {
  numerator_ = 0;
  denominator_ = 1;
}

Rational::Rational(int x) {
  numerator_ = x;
  denominator_ = 1;
}

Rational::Rational(int numer, int denom) {
  if (denom == 0) {
    throw RationalDivisionByZero{};
  }
  numerator_ = static_cast<int64_t>(numer);
  denominator_ = static_cast<int64_t>(denom);
  FractionReduction(numerator_, denominator_);
}

int Rational::GetNumerator() const {
  return numerator_;
}

int Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(int numer) {
  numerator_ = numer;
  FractionReduction(numerator_, denominator_);
}

void Rational::SetDenominator(int denom) {
  if (denom == 0 || denominator_ == 0) {
    throw RationalDivisionByZero{};
  } else {
    denominator_ = denom;
  }
  FractionReduction(numerator_, denominator_);
}

Rational::~Rational() = default;

void Rational::Simply() {
  int64_t numer = numerator_;
  int64_t denom = denominator_;
  FractionReduction(numer, denom);
  SetNumerator(numer);
  SetDenominator(denom);
}

Rational operator+(const Rational& left, const Rational& right) {
  Rational temp;
  int64_t denom = std::lcm(left.denominator_, right.denominator_);
  int64_t factleft = denom / left.denominator_;
  int64_t factright = denom / right.denominator_;
  int64_t numeratorlast = left.numerator_ * factleft + right.numerator_ * factright;
  FractionReduction(numeratorlast, denom);
  temp.SetNumerator(numeratorlast);
  temp.SetDenominator(denom);
  temp.Simply();
  return temp;
}

Rational operator-(const Rational& left, const Rational& right) {
  return left + (-right);
}

Rational operator*(const Rational& left, const Rational& right) {
  Rational temp;
  int64_t numer = left.numerator_ * right.numerator_;
  int64_t denom = left.denominator_ * right.denominator_;
  FractionReduction(numer, denom);
  temp.SetNumerator(numer);
  temp.SetDenominator(denom);
  return temp;
}

Rational operator/(const Rational& left, const Rational& right) {
  if (right.numerator_ == 0) {
    throw RationalDivisionByZero{};
  }
  Rational temp_1(left.GetNumerator(), left.GetDenominator());
  Rational temp_2(right.GetDenominator(), right.GetNumerator());
  return temp_1 * temp_2;
}

bool operator<(const Rational& left, const Rational& right) {
  return ((left - right).numerator_ < 0);
}

bool operator>(const Rational& left, const Rational& right) {
  return (right < left);
}

bool operator==(const Rational& left, const Rational& right) {
  return !(left < right || right < left);
}

bool operator!=(const Rational& left, const Rational& right) {
  return !(left == right);
}

bool operator<=(const Rational& left, const Rational& right) {
  return ((left < right) || (left == right));
}

bool operator>=(const Rational& left, const Rational& right) {
  return ((left > right) || (left == right));
}

std::ostream& operator<<(std::ostream& out, const Rational& frac) {
  out << frac.numerator_;
  if (frac.numerator_ != 0 && frac.denominator_ != 1) {
    out << "/" << frac.denominator_;
  }
  return out;
}

std::istream& operator>>(std::istream& in, Rational& frac) {
  int numer, denom;
  in >> numer;
  if (in.peek() == '/') {
    in.ignore();
    in >> denom;
  } else {
    denom = 1;
  }
  frac.SetNumerator(numer);
  frac.SetDenominator(denom);
  return in;
}

Rational& Rational::operator=(const Rational& frac) {
  SetNumerator(frac.GetNumerator());
  SetDenominator(frac.GetDenominator());
  return *this;
}

Rational& Rational::operator+=(const Rational& frac) {
  *this = *this + frac;
  return *this;
}

Rational& Rational::operator-=(const Rational& frac) {
  *this = *this - frac;
  return *this;
}

Rational& Rational::operator*=(const Rational& frac) {
  *this = *this * frac;
  return *this;
}

Rational& Rational::operator/=(const Rational& frac) {
  *this = *this / frac;
  return *this;
}
Rational& Rational::operator++() {
  *this = *this + 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational before = *this;
  *this = *this + 1;
  return before;
}

Rational& Rational::operator--() {
  *this = *this - 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational before = *this;
  *this = *this - 1;
  return before;
}

Rational Rational::operator+() const {
  return *this;
}

Rational Rational::operator-() const {
  Rational temp;
  temp.SetNumerator(-GetNumerator());
  temp.SetDenominator(GetDenominator());
  return temp;
}