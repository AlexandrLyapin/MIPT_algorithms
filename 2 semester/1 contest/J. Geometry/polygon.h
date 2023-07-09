#ifndef POLYGON
#define POLYGON
#include "point.h"
#include <vector>

namespace geometry {
  class Polygon : public IShape {
   public:
    std::vector<Point> vertices;

    Polygon() = default;
    explicit Polygon(const std::vector<Point>& vertices);

    Polygon& Move(const Vector& move_vec) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    Polygon* Clone() const override;

    std::string ToString() const override;
  };
}

#endif