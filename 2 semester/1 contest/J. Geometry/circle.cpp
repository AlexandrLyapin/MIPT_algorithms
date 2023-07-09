#include "../circle.h"
#include <cstdint>
#include "../segment.h"
#include "../vector.h"
// #include "circle.h"
// #include "point.h"
// #include "segment.h"

namespace geometry {
  Circle::Circle(const Point& center, int64_t radius) : radius(radius), center(center) {}

  Circle& Circle::Move(const Vector& move_vec) {
    center.Move(move_vec);
    return *this;
  }

  bool Circle::ContainsPoint(const Point& point) const {
    return SquaredLength({point.x - center.x, point.y - center.y}) <= radius * radius;
  }

  bool Circle::CrossesSegment(const Segment& seg) const {
    Vector vec_oa{seg.start.x - center.x, seg.start.y - center.y};
    Vector vec_ob{seg.end.x - center.x, seg.end.y - center.y};
    Vector seg_vector{seg.end.x - seg.start.x, seg.end.y - seg.start.y};
    if (SquaredLength(vec_oa) < radius * radius && SquaredLength(vec_ob) < radius * radius) {
      return false;
    }
    int64_t rounded_square_distance_to_center = 0;
    int64_t remain = 0;
    if (ScalarProduct(-vec_oa, seg_vector) <= 0) {
      rounded_square_distance_to_center = SquaredLength(vec_oa);
    } else if (ScalarProduct(-vec_ob, -seg_vector) <= 0){
      rounded_square_distance_to_center = SquaredLength(vec_ob);
    } else {
      rounded_square_distance_to_center = VectorProduct(vec_oa, seg_vector) * VectorProduct(vec_oa, seg_vector) / SquaredLength(seg_vector);
      remain = VectorProduct(vec_oa, seg_vector) * VectorProduct(vec_oa, seg_vector) % SquaredLength(seg_vector);
    }
    return ((rounded_square_distance_to_center == radius * radius && remain == 0) || rounded_square_distance_to_center < radius * radius);
}

  Circle* Circle::Clone() const {
    auto copy = new Circle(*this);
    return copy;
  }

  std::string Circle::ToString() const {
    std::string output = "Circle(";
    output += center.ToString() + ", " + std::to_string(radius) + ")";
    return output;
  }
}