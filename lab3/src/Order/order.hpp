#pragma once

#include "../utilies.hpp"
#include "../Transports/transport.hpp"
#include "../Track/track.hpp"

using std::string;

enum Type {
	Turbo,
	Standart,
	Economy
};

class Order {
private:
	double cost;
	int volume;
	string start_point;
	string finish_point;
	enum Type type;
	Track track;

public:
	Order();
	Order(Type deliv, string start_p, string finish_p, int vol);

	int decr(string str);
	int** matrix_upd(Type type);
	int* optim(int** arr, int begin_point, int end_point);
	Track best(string start_p, string finish_p, Type deliv, int volume);
};
