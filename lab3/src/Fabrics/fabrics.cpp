#include <memory>

#include "../Transports/transport.hpp"
#include "../Transports/Car/car.hpp"
#include "../Transports/Plane/plane.hpp"
#include "../Transports/Train/train.hpp"

#include "fabrics.hpp"

/* ----------------- Car entity creation ----------------- */

Transport* CarFabric::make_transport(int _speed, int _volume, double _price, int _distance) {
  Car car = std::unique_ptr<Transport>(new Car());
  car->set_speed(_speed);
  car->set_volume(_volume);
  car->set_price(_price);
  car->set_distance(_distance);
  return car;
}

/* ----------------- Train entity creation ----------------- */


Transport* TrainFabric::make_transport(int _speed, int _volume, double _price, int _distance) {
  Train train = std::unique_ptr<Transport>(new Train());
  train->set_speed(_speed);
  train->set_volume(_volume);
  train->set_price(_price);
  train->set_distance(_distance);
  return train;
}

/* ----------------- Plane entity creation ----------------- */


Transport* PlaneFabric::make_transport(int _speed, int _volume, double _price, int _distance) {
  Plane plane = std::unique_ptr<Transport>(new Plane());
  plane->set_speed(_speed);
  plane->set_volume(_volume);
  plane->set_price(_price);
  plane->set_distance(_distance);
  return plane;
}
