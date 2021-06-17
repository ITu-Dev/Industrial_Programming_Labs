#include "plane.hpp"

#include <tuple>

using std::tuple;
using std::make_tuple;

Plane::Plane() : Transport(make_tuple(300, 100, 500), 0) {}

Plane::Plane(std::tuple<int, int, double> params, int distance) :
	Transport(params, distance) {}
