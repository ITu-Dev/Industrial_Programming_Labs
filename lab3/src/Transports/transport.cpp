#include "transport.hpp"

#include <tuple>

using std::tuple;

Transport::Transport() {
	speed = 0;
	volume = 0;
	price = 0.0f;
	distance = 0;
}

Transport::Transport(std::tuple<int, int, double> transport_params, int _distance) :
	speed(get<0>(transport_params)),
	volume(get<1>(transport_params)),
	price(get<2>(transport_params)),
	distance(_distance) {}

double Transport::get_cost(int mass, int dist) {
	return (mass / volume) * get_time(dist) * price;
}

double Transport::get_time(int dist) const {
	return dist / speed;
}

int Transport::get_distance() const { return distance; };
void Transport::set_speed(int _speed) { speed = _speed; }
void Transport::set_volume(int _volume) { volume = _volume; }
void Transport::set_price(double _price) { price = _price; }
void Transport::set_distance(int _distance) { distance = _distance; }
