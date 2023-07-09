#include "../point.h"
#include "../segment.h"

// #include "point.h"
// #include "segment.h"

namespace geometry {
  Point::Point(int64_t x, int64_t y) : x(x), y(y) {}

  Point& Point::Move(const Vector& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
  }

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool Point::ContainsPoint(const Point& point) const {
    return *this == point;
  }

  bool Point::CrossesSegment(const Segment& seg) const {
    return seg.ContainsPoint(*this);
  }

  Vector operator-(const Point& lhs, const Point& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
  }

  Point* Point::Clone() const {
    auto copy = new Point(x, y);
    return copy;
  }

  std::string Point::ToString() const {
    std::string output;
    output += "Point(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    return output;
  }
}