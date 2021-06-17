#pragma once

#include <tuple>
#include <memory>

using std::tuple;

class Transport {
private:
	int speed;
	int volume;
	double price;
	int distance;
public:
	Transport();
	Transport(std::tuple<int, int, double> transport_params, int distance);
	~Transport() = default;

	double get_cost(int mass, int dist);
	double get_time(int dist) const;

	int  get_distance() const;
	void set_speed(int speed);
	void set_volume(int volume);
	void set_price(double price);
	void set_distance(int distance);
};
