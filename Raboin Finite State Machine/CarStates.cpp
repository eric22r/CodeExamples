#include "CarStates.h"
#include <Windows.h>
#include <iostream>
//Destructor
AbstractState::~AbstractState(){}

//Sets state and deletes temp var
void AbstractState::setState(Car& car, AbstractState* state)
{
	AbstractState* x = car.m_State;
	car.m_State = state;
	delete x;
}

//May not use this
void AbstractState::updateDrive(Car& car, int stage)
{
	car.stage = stage;
}

//Destructor
Parked::~Parked(){}

//Accelerates and sets next state
void Parked::accelerate(Car& car, float accTime)
{
	std::cout << "Parked.\n";
	std::cout << "Accelerating up to 13mph....\n";
	Sleep(accTime);
	setState(car, new Driving());
}

//Decelerates and sets next state
void Parked::decelerate(Car& car, float accTime)
{
	std::cout << "Decelerating to park...\n";
	Sleep(accTime);
	std::cout << "Parked.\n";
	setState(car, new Parked());
}

//Destructor
Driving::~Driving(){}

//Accelerates and sets next state
void Driving::accelerate(Car& car, float accTime)
{
	std::cout << "Reaching 13 mph....\n";
	Sleep(accTime);
	setState(car, new Idle());
}

//Decelerates and sets next state
void Driving::decelerate(Car& car, float accTime)
{
	std::cout << "Decelerating to parked....\n";
	Sleep(accTime);
	std::cout << "Parked.\n";
	setState(car, new Parked());
}
//Destructor
Idle::~Idle(){}

//Cruises and sets next state
void Idle::accelerate(Car& car, float accTime)
{
	std::cout << "Cruising.....\n";
	Sleep(accTime);
	setState(car, new Driving());
}
//Cruises and sets next state
void Idle::decelerate(Car& car, float accTime)
{
	std::cout << "Cruising.....\n";
	Sleep(accTime);
	setState(car, new Driving());
}