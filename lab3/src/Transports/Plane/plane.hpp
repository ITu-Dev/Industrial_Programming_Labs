#include "../transport.hpp"

#include <tuple>

using std::tuple;

class Plane : public Transport {
public:
	Plane();
	Plane(std::tuple<int, int, double> params, int distance);
};
