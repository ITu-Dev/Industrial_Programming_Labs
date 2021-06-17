#pragma once

#include "../Transports/transport.hpp"

class TransportFabric {
public:
	virtual ~TransportFabric();
	virtual Transport* make_transport(int _speed, int _volume, double _price, int _distance);
};

class CarFabric : public TransportFabric {
public:
	Transport* make_transport(int _speed, int _volume, double _price, int _distance) override;
};

class TrainFabric : public TransportFabric {
public:
	Transport* make_transport(int _speed, int _volume, double _price, int _distance) override;
};

class PlaneFabric : public TransportFabric {
public:
	Transport* make_transport(int _speed, int _volume, double _price, int _distance) override;
};
