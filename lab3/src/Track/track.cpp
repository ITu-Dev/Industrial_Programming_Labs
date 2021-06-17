#include <list>

#include "track.hpp"
#include "../Transport/transport.hpp"

using std::list;

Track::Track(list<Transport> transports, int volume) {
	for (auto it = transports.begin(); it != transports.end(); it++) {
		cost += (*it).get_cost(volume, (*it).get_distance());
		time += (*it).get_time((*it).get_distance());
	}
}

Track::Track() { cost = time = volume = 0; }

double Track::get_cost() { return cost; }
