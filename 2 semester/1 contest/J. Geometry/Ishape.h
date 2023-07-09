#ifndef ISHAPE
#define ISHAPE
#include "vector.h"
#include <string>

namespace geometry {
  class Segment;
  class Point;
  class IShape {
   public:
    virtual ~IShape() = default;
    virtual IShape& Move(const Vector& move_vec) = 0;
    virtual bool ContainsPoint(const Point& point) const = 0;
    virtual bool CrossesSegment(const Segment& seg) const = 0;
    virtual IShape* Clone() const = 0;
    virtual std::string ToString() const = 0;
  };
}

#endif