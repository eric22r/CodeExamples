#include <iostream>
#include <dos.h>
#include <string>
#include <sstream>
#include "Pacman.h"
#include <time.h> 

using namespace std;

int rNumber;

int Random(int _choice)
{
	rNumber = rand() % _choice + 1;

	return rNumber;
}

Pacman::Pacman()
{
	lives = 1;
	speed = 5;
	isAlive = true;
	position.x = 3;
	position.y = 5;
}

Pacman::Pacman(float _speed)
{
	lives = 1;
	speed = _speed;
	isAlive = true;
	position.x = 4;
	position.y = 5;
}

Pacman::Pacman(float _speed, bool _isAlive)
{
	lives = 1;
	speed = _speed;
	isAlive = _isAlive;
	position.x = 4;
	position.y = 5;
}

void Pacman::SetLives(int _lives)
{
	lives = _lives;
}

int Pacman::GetLives()
{
	return lives;
}

void Pacman::SetSpeed(float _speed)
{
	speed = _speed;
}

float Pacman::GetSpeed()
{
	return speed;
}

void Pacman::SetPosition(Coord _position)
{
	position = _position;
}

Coord Pacman::GetPosition()
{
	return position;
}

void Pacman::SetVelocity(int x, int y)
{

	pacVel.x = x;
	pacVel.y = y;
}

bool Pacman::isColliding(Ghost _ghost)
{
	//bool colliding = false;
	//if (position.x == ghost.GetPosition().x && position.y == ghost.GetPosition().y)
	//{
	//	colliding = true;
	//}
	return colliding;
}

void Pacman::RandomizePosition()
{
	//Set Random X (1-80)
	//int randNum = rand() % (max - min + 1) + min;
	position.x = (rand() % (80 - 1 + 1) + 1);

	//Set Random Y (1-20)
	position.y = (rand() % (20 - 1 + 1) + 1);

}

void Pacman::Move()
{
	Coord newPos = GetPosition();

	newPos.x += pacVel.x;
	newPos.y += pacVel.y;

	if (newPos.x > 32)
	{
		newPos.x = 32;
		pacVel.x *= -1;
	}
	else if (newPos.x < 0)
	{
		newPos.x = 0;
		pacVel.x *= -1;
	}
	if (newPos.y > 23)
	{
		newPos.y = 0;
	}
	else if (newPos.y < 0)
	{
		newPos.y = 23;
	}

	SetPosition(newPos);
}
