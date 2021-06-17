#include "car.hpp"

#include <tuple>

using std::tuple;
using std::make_tuple;

Car::Car() : Transport(make_tuple(60, 50, 100), 0) {}

Car::Car(std::tuple<int, int, double> params, int distance) :
	Transport(params, distance) {};
