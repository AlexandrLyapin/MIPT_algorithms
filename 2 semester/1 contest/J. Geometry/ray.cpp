#include "../ray.h"
#include "../segment.h"

// #include "ray.h"
// #include "point.h"
// #include "segment.h"

namespace geometry {
  Ray::Ray(const Point& start, const Vector& direction) : start(start), direction(direction) {}
  Ray::Ray(const Point& start, const Point& end) : start(start), direction({end.x - start.x, end.y - start.y}) {}

  Ray& Ray::Move(const Vector& move_vec) {
    start.Move(move_vec);
    return *this;
  }

  bool Ray::ContainsPoint(const Point& point) const {
    Vector vec{point.x - start.x, point.y - start.y};
    return VectorProduct(direction, vec) == 0 && ScalarProduct(vec, direction) >= 0;
  }

  bool Ray::CrossesSegment(const Segment& seg) const {
    Vector vec_ab{seg.end.x - seg.start.x, seg.end.y - seg.start.y};
    Vector vec_oa{seg.start.x - start.x, seg.start.y - start.y};
    Vector vec_ob{seg.end.x - start.x, seg.end.y - start.y};
    if (VectorProduct(direction, vec_oa) * VectorProduct(direction, vec_ob) <= 0) {
      return VectorProduct(-vec_oa, vec_ab) * VectorProduct(direction, vec_ab) < 0 || ContainsPoint(seg.start) || ContainsPoint(seg.end);
    }
    return false;
  }

  Ray* Ray::Clone() const {
    auto copy = new Ray(start, direction);
    return copy;
  }

  std::string Ray::ToString() const {
    std::string output;
    output += "Ray(" + start.ToString() + ", " + direction.ToString() + ")";
    return output;
  }
}