#ifndef SEGMENT
#define SEGMENT
#include "point.h"

namespace geometry {
  class Segment : public IShape {
   public:
    Point start;
    Point end;

    Segment() = default;
    Segment(const Point& start, const Point& end);
    Segment(const Segment& seg) = default;
    Segment& operator=(const Segment& seg) = default;
    Segment(Segment&& seg) = default;
    Segment& operator=(Segment&& seg) = default;

    Segment& Move(const Vector& move_vec) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& other) const override;

    Segment* Clone() const override;

    std::string ToString() const override;
  };

  double DistanceToSegment(const Segment &seg, const Point &point);
}
#endif