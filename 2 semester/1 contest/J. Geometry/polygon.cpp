#include "../polygon.h"
#include "../segment.h"
#include "..//ray.h"

// #include "polygon.h"
// #include "point.h"
// #include "segment.h"
// #include "ray.h"

namespace geometry {
  Polygon::Polygon(const std::vector<Point>& vertices) : vertices(vertices) {}

  Polygon& Polygon::Move(const Vector& move_vec) {
    for (auto& vertice : vertices) {
      vertice.Move(move_vec);
    }
    return *this;
  }

  bool Polygon::ContainsPoint(const Point& point) const {
    int intersection_count = 0;
    Ray check_ray = Ray(point, Vector{1, 0});
    size_t size = vertices.size();
    for (size_t i = 0; i < size; ++i) {
      Segment side = (i == size - 1) ? Segment(vertices[i], vertices[0]) : Segment(vertices[i], vertices[i + 1]);
      if (side.ContainsPoint(point)) {
        return true;
      }
      if (check_ray.CrossesSegment(side)) {
        bool is_first_on_ray = check_ray.ContainsPoint(side.start);
        bool is_second_on_ray = check_ray.ContainsPoint(side.end);
        if (!is_first_on_ray && !is_second_on_ray) {
          ++intersection_count;
        } else if (is_first_on_ray && side.start.y > side.end.y) {
          ++intersection_count;
        } else if (is_second_on_ray && side.end.y > side.start.y) {
          ++intersection_count;
        }
      }
    }
    return intersection_count % 2 != 0;
  }

  bool Polygon::CrossesSegment(const Segment& seg) const {
    size_t size = vertices.size();
    for (size_t i = 0; i < size; ++i) {
      Segment side = (i == size - 1) ? Segment(vertices[i], vertices[0]) : Segment(vertices[i], vertices[i + 1]);
      if (side.CrossesSegment(seg)) {
        return true;
      }
    }
    return false;
  }

  Polygon* Polygon::Clone() const {
    auto copy = new Polygon(*this);
    return copy;
  }

  std::string Polygon::ToString() const {
    std::string output = "Polygon(";
    for (auto vertice : vertices) {
      output += vertice.ToString() + ", ";
    }
    output.pop_back();
    output.pop_back();
    output.push_back(')');
    return output;
  }
}
