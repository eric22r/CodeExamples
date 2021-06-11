#include "Car.h"

Car::Car(int state)
{
	//Determines state to start in depending on passed variable.
	if (state == 1)
		m_State = new Parked();
	if (state == 2)
		m_State = new Driving();
	if (state == 3)
		m_State = new Idle();
}

Car::~Car() {
	delete m_State;
}

void Car::accelerate(float accTime) {
	m_State->accelerate(*this, accTime);
}

void Car::decelerate(float accTime) {
	m_State->decelerate(*this, accTime);
}