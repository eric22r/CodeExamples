#pragma once
#include "Car.h"
#include <exception>
#include <stdexcept>

class Car;

class AbstractState {
public:
	virtual void accelerate(Car& car, float accTime) = 0;
	virtual void decelerate(Car& car, float accTime) = 0;
	virtual ~AbstractState();
protected:
	void setState(Car& car, AbstractState* state);
	void updateDrive(Car& car, int stage);
};

class Parked : public AbstractState {
public:
	virtual void accelerate(Car& car, float accTime);
	virtual void decelerate(Car& car, float accTime);
	virtual ~Parked();
};

class Driving : public AbstractState {
public:
	virtual void accelerate(Car& car, float accTime);
	virtual void decelerate(Car& car, float accTime);
	virtual ~Driving();
};

class Idle : public AbstractState {
public:
	virtual void accelerate(Car& car, float accTime);
	virtual void decelerate(Car& car, float accTime);
	virtual ~Idle();
};