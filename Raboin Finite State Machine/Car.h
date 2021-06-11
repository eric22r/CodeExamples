#pragma once

#include "CarStates.h"

class AbstractState;

class Car {
	friend class AbstractState;
public:
		int stage;
		Car(int state);
		~Car();
		void accelerate(float accTime);
		void decelerate(float accTime);
	private:
		unsigned int carTrips;
		AbstractState* m_State;

};
