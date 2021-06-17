#include "train.hpp"

#include <tuple>

using std::tuple;
using std::make_tuple;

Train::Train() : Transport(make_tuple(100, 500, 200), 0) {}

Train::Train(std::tuple<int, int, double> params, int distance) :
	Transport(params, distance) {}
