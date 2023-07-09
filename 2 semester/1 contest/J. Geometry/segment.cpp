#include <cmath>
#include "../point.h"
#include "../segment.h"
#include "../ray.h"
// #include "point.h"
// #include "segment.h"

namespace geometry {

  int Sign(int64_t value) {
    if (value > 0) {
      return 1;
    }
    if (value == 0) {
      return 0;
    }
    return -1;
  }

  Segment::Segment(const Point& start, const Point& end) : start(start), end(end) {}

  Segment& Segment::Move(const Vector& move_vec) {
    start.Move(move_vec);
    end.Move(move_vec);
    return *this;
  }

  bool Segment::ContainsPoint(const Point& point) const {
    Vector to_point{point.x - start.x, point.y - start.y};
    Vector seg_vector{end.x - start.x, end.y - start.y};
    return VectorProduct(seg_vector, to_point) == 0 && ScalarProduct(to_point, seg_vector) >= 0
            && SquaredLength(to_point) <= SquaredLength(seg_vector);
    // Ray first = Ray(start, end);
    // Ray second = Ray(end, start);
    // return first.ContainsPoint(point) && second.ContainsPoint(point);
  }

  bool Segment::CrossesSegment(const Segment& other) const {
    Vector vec_ab{end.x - start.x, end.y - start.y};
    Vector vec_cd{other.end.x - other.start.x, other.end.y - other.start.y};
    Vector vec_ac{other.start.x - start.x, other.start.y - start.y};
    Vector vec_ad{other.end.x - start.x, other.end.y - start.y};
    Vector vec_cb{end.x - other.start.x, end.y - other.start.y};
    int prod_vector_prod_ab = Sign(VectorProduct(vec_ab, vec_ac)) * Sign(VectorProduct(vec_ab, vec_ad));
    int prod_vector_prod_cd = Sign(VectorProduct(vec_cd, -vec_ac)) * Sign(VectorProduct(vec_cd, vec_cb));
    if (prod_vector_prod_ab < 0 && prod_vector_prod_cd < 0) {
      return true;
    }
    if (prod_vector_prod_ab > 0 || prod_vector_prod_cd > 0) {
      return false;
    }
    return ((ScalarProduct(vec_ab, vec_ac) >= 0 && ScalarProduct(vec_ab, vec_ac) <= SquaredLength(vec_ab))) ||
           ((ScalarProduct(vec_ab, vec_ad) >= 0) && (ScalarProduct(vec_ab, vec_ad) <= SquaredLength(vec_ab)));
  }

  Segment* Segment::Clone() const {
    auto copy = new Segment(start, end);
    return copy;
  } 

  std::string Segment::ToString() const {
    std::string output;
    output += "Segment(" + start.ToString() + ", " + end.ToString() + ")";
    return output;
  }

  uint64_t SquaredDistanceToSegmentRounded(const Segment& seg, const Point& point) {
    Vector v1{point.x - seg.start.x, point.y - seg.start.y};
    Vector v2{point.x - seg.end.x, point.y - seg.end.y};
    Vector seg_vector{seg.end.x - seg.start.x, seg.end.y - seg.start.y};
    if (ScalarProduct(v1, seg_vector) <= 0) {
      return SquaredLength(v1);
    }
    if (ScalarProduct(v2, -seg_vector) <= 0) {
      return SquaredLength(v2);
    }
    return (VectorProduct(seg_vector, v1) * VectorProduct(seg_vector, v1)) / SquaredLength(seg_vector);
  }

}