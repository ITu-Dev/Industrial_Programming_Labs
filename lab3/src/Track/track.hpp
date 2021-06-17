#pragma once
#include <list>

class Transport;

class Track {
private:
	double cost;
	double time;
	int volume;
public:
	Track();
	~Track() = default;
	Track(std::list<Transport> transports, int volume);

	double get_cost();
};
