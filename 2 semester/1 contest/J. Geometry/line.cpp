#include "../line.h"
#include "../segment.h"

// #include "line.h"
// #include "point.h"
// #include "segment.h"

namespace geometry {
  Line::Line(int64_t a, int64_t b, int64_t c) : a(a), b(b), c(c) {}
  Line::Line(const Point& first, const Point& second) : a(second.y - first.y), b(first.x - second.x), c(-a * first.x - b * first.y) {}

  inline int64_t Line::FindDotValueOnLine(const Point& point) const {
    return a * point.x + b * point.y + c;
  }

  Line& Line::Move(const Vector& move_vec) {
    c -= ScalarProduct(move_vec, {a, b});
    return *this;
  }

  bool Line::ContainsPoint(const Point& point) const {
    return FindDotValueOnLine(point) == 0;
  }

  bool Line::CrossesSegment(const Segment& seg) const {
    return FindDotValueOnLine(seg.start) * FindDotValueOnLine(seg.end) <= 0;
  }

  Line* Line::Clone() const {
    auto copy = new Line(*this);
    return copy;
  }

  std::string Line::ToString() const {
    std::string output;
    int64_t gcd = std::gcd(std::gcd(a, b), c);
    output += "Line(" + std::to_string(a / gcd) + ", " + std::to_string(b / gcd) + ", " + std::to_string(c / gcd) + ")";
    return output;
  }
}