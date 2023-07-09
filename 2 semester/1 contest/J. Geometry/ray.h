#ifndef RAY
#define RAY
#include "point.h"

namespace geometry {
  class Ray : public IShape {
   public:
    Point start;
    Vector direction;

    Ray() = default;
    Ray(const Point& start, const Vector& direction);
    Ray(const Point& start, const Point& end);
    
    Ray& Move(const Vector& move_vec) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    Ray* Clone() const override;

    std::string ToString() const override;
  };
}

#endif