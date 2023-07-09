#include "../vector.h"
// #include "vector.h"

namespace geometry {
  Vector Vector::operator+() const {
    return *this;
  }

  Vector Vector::operator-() const {
    return {-x, -y};
  }

  bool Vector::operator==(const Vector& other) const {
    return (x == other.x) && (y == other.y);
  }

  bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
  }

  Vector& Vector::operator+=(const Vector& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector& Vector::operator-=(const Vector& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vector& Vector::operator*=(int64_t multiplier) {
    x *= multiplier;
    y *= multiplier;
    return *this;
  }

  Vector& Vector::operator/=(int64_t delimeter) {
    x /= delimeter;
    y /= delimeter;
    return *this;
  }

  Vector operator+(const Vector& lhs, const Vector& rhs) {
    Vector tmp = lhs;
    tmp += rhs;
    return tmp;
  }

  Vector operator-(const Vector& lhs, const Vector& rhs) {
    Vector tmp = lhs;
    tmp -= rhs;
    return tmp;
  }

  Vector operator*(const Vector& vec, int64_t multiplier) {
    Vector tmp = vec;
    tmp *= multiplier;
    return tmp;
  }

  Vector operator*(int64_t multiplier, const Vector& vec) {
    Vector tmp = vec;
    tmp *= multiplier;
    return tmp;
  }

  Vector operator/(const Vector& vec, int64_t delimeter) {
    Vector tmp = vec;
    tmp /= delimeter;
    return tmp;
  }

  int64_t VectorProduct(const Vector& lhs, const Vector& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }

  int64_t SquaredLength(const Vector& vec) {
    return vec.x * vec.x + vec.y * vec.y;
  }

  int64_t ScalarProduct(const Vector& lhs, const Vector& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }

  std::string Vector::ToString() const {
    std::string output;
    output += "Vector(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    return output;
  }
}
