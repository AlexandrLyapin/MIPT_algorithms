#ifndef POINT
#define POINT
#include "Ishape.h"

namespace geometry {

  class Point : public IShape {  
   public:
    int64_t x;
    int64_t y;

    Point() = default;
    Point(int64_t x, int64_t y);
    Point(const Point&) = default;
    Point& operator=(const Point&) = default;
    Point(Point&&) = default;
    Point& operator=(Point&&) = default;

    Point& Move(const Vector& vec) override;

    bool operator==(const Point& other) const;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    Point* Clone() const override;

    std::string ToString() const override;
  };

  Vector operator-(const Point& lhs, const Point& rhs);
}

#endif