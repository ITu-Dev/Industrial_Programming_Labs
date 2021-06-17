#include "../transport.hpp"

#include <tuple>

using std::tuple;

class Train : public Transport {
public:
	Train();
	Train(std::tuple<int, int, double> params, int distance);
};
