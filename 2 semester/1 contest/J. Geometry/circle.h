#ifndef CIRCLE
#define CIRCLE

#include "point.h"

namespace geometry {
  class Circle : public IShape {
   public:
    int64_t radius;
    Point center;

    Circle() = default;
    Circle(const Point& center, int64_t radius);

    Circle& Move(const Vector& move_vec) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    Circle* Clone() const override;

    std::string ToString() const override;
  };
}

#endif