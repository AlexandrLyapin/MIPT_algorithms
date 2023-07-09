#ifndef VECTOR
#define VECTOR

#include <string>

namespace geometry {
  class Vector {
   public:
    int64_t x;
    int64_t y;
    Vector operator+() const;
    Vector operator-() const;
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(int64_t multiplier);
    Vector& operator/=(int64_t delimeter);
    std::string ToString() const;
  };

  Vector operator+(const Vector& lhs, const Vector& rhs);
  Vector operator-(const Vector& lhs, const Vector& rhs);
  Vector operator*(const Vector& vec, int64_t multiplier);
  Vector operator/(const Vector& vec, int64_t delimeter);
  Vector operator*(int64_t multiplier, const Vector& vec);
  int64_t VectorProduct(const Vector& lhs, const Vector& rhs);
  int64_t ScalarProduct(const Vector& lhs, const Vector& rhs);
  int64_t SquaredLength(const Vector& vec);
}



#endif