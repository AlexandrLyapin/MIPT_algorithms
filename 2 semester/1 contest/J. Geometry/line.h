#ifndef LINE
#define LINE
#include "Ishape.h"
#include <numeric>

namespace geometry {
  class Line : public IShape {
   public:
    int64_t a;
    int64_t b;
    int64_t c;
    Line() = default;
    Line(int64_t a, int64_t b, int64_t c);
    Line(const Point& first, const Point& second);

    inline int64_t FindDotValueOnLine(const Point&) const;

    Line& Move(const Vector& move_vec) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    Line* Clone() const override;

    std::string ToString() const override;
  };
}

#endif