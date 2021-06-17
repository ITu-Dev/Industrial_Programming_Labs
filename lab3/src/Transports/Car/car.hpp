#include "../transport.hpp"

#include <tuple>

using std::tuple;

class Car : public Transport {
public:
	Car();
	Car(std::tuple<int, int, double> params, int distance);
};
