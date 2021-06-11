#include "Ghost.h"
#include<Windows.h>


Ghost::Ghost(int state, int xPos, int yPos)
{
	if (state == 1)
	{
		m_State = new PinkyState();
	}
	if (state == 2)
	{
		m_State = new InkyState();

	}
	if (state == 3)
	{
		m_State = new BlinkyState();

	}
	if (state == 4)
	{
		m_State = new ClydeState();
	}
}

Ghost::~Ghost(){
	delete m_State;
}

void Ghost::SetPosition(Coord2 _position)
{
	position = _position;
}

Coord2 Ghost::GetPosition()
{
	return position;
}

void Ghost::Move(int velX, int velY)
{
	Coord2 newPos = GetPosition();
	ghostVel.x = velX;
	ghostVel.y = velY;
	newPos.x += ghostVel.x;
	newPos.y += ghostVel.y;

	if (newPos.x > 29)
	{
		newPos.x = 29;
		ghostVel.x *= -1;
	}
	else if (newPos.x < 1)
	{
		newPos.x = 1;
		ghostVel.x *= -1;
	}
	if (newPos.y > 23)
	{
		newPos.y = 23;
	}
	else if (newPos.y < 1)
	{
		newPos.y = 1;
	}

	SetPosition(newPos);
}

void Ghost::chase(int x, int y)
{
	//change this to player target
	m_State->chase(*this, x, y);


}

void Ghost::evade(int x, int y)
{
	//change this to player target and do opp of chase
	m_State->evade(*this, -x, -y);
}

void Ghost::returnToBase(int x, int y)
{

	m_State->returnToBase(*this, 16, 9);
	
	//once at house, resume to chase
	m_State->chase(*this, x, y);
}