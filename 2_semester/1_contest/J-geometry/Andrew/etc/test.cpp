#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../circle.h"
#include "../line.h"
#include "../other.h"
#include "../point.h"
#include "../polygon.h"
#include "../ray.h"
#include "../segment.h"
#include "../vector.h"

using namespace std::literals;
using namespace geometry;

// g++safe test.cpp ../src/* -o test && ./test

int main() {
	// Point x(0, 0);
	// Point y(1, 0);

	Point a(0, -5);
	Point b(-54, 4);

	Vector vec_ab(a, b);
	Segment seg_ab(a, b);

  // Ray r(x, y);

  // Output(r);
	// Output(seg_ab);

	// Output("Line(r) cross seg_ab: ", Line(r).CrossesSegment(seg_ab));

	// Output("r cross seg_ab:", r.CrossesSegment(seg_ab));
	// Output("r cross a:", r.ContainsPoint(a));
	// Output("r cross b:", r.ContainsPoint(b));

  // r.Move(vec_ab);
  // Output(r);

	// int n = 8;

	// Polygon poly({
	// 	{0, 0}, 
	// 	{0, 4},
	// 	{4, 0},
	// 	{4, 4}
	// });

	// for (int y = -1; y < 6; ++y) {
	// 	Output("y =", y, ": -------------------------------");
	// 	for (int x = -1; x < 6; ++x) {
  //     Point p(x, y);
  //     Output(p, poly.ContainsPoint(p));
  //   }
	// }

	Circle c({0, 0}, 5);

	Output(c.CrossesSegment(seg_ab));
}
