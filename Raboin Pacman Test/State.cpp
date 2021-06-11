#include "State.h"
#include "Ghost.h"
#include "Pacman.h"
#include <Windows.h>
#include <iostream>

AbstractState::~AbstractState(){}

void AbstractState::setState(Ghost& ghost, AbstractState* state)
{
	AbstractState* x = ghost.m_State;
	ghost.m_State = state;
	delete x;
}

void AbstractState::updateState(Ghost& ghost, int stage)
{
	ghost.stage = stage;
}

void PacmanMoveState::AbleToMove(Pacman& pacman, int x, int y)
{
	pacman.SetVelocity(x, y);
}
void PacmanMoveState::Killed(Pacman& pacman, int x, int y)
{
	pacman.SetLives(pacman.GetLives() - 1);
}

PinkyState::~PinkyState(){}

void PinkyState::chase(Ghost& ghost, int x, int y)
{
	ghost.Move(x, y);
	//SetState to evade for powerpill?
}

void PinkyState::evade(Ghost& ghost, int x, int y)
{
	ghost.Move(x, y);
	//SetState to chase for powerpill wearoff?
}
void PinkyState::returnToBase(Ghost& ghost, int x, int y)
{
	Coord2 ghPos;
	ghPos.x = x;
	ghPos.y = y;
	ghost.SetPosition(ghPos);
	//return to chase when reaches house
}
InkyState::~InkyState() {}
void InkyState::chase(Ghost& ghost, int x, int y)
{
	ghost.Move(x, y);
	//SetState to evade for powerpill?
}

void InkyState::evade(Ghost& ghost, int x, int y)
{
	ghost.Move(x, y);
	//SetState to chase for powerpill wearoff?
}
void InkyState::returnToBase(Ghost& ghost, int x, int y)
{
	Coord2 ghPos;
	ghPos.x = x;
	ghPos.y = y;
	ghost.SetPosition(ghPos);
	//return to chase when reaches house
}
BlinkyState::~BlinkyState() {}
void BlinkyState::chase(Ghost& ghost, int x, int y)
{
	ghost.Move(x, y);
	//SetState to evade for powerpill?
}

void BlinkyState::evade(Ghost& ghost, int x, int y)
{
	ghost.Move(x, y);
	//SetState to chase for powerpill wearoff?
}
void BlinkyState::returnToBase(Ghost& ghost, int x, int y)
{
	Coord2 ghPos;
	ghPos.x = x;
	ghPos.y = y;
	ghost.SetPosition(ghPos);
	//return to chase when reaches house
}
ClydeState::~ClydeState() {}
void ClydeState::chase(Ghost& ghost, int x, int y)
{
	ghost.Move(x, y);
	//SetState to evade for powerpill?
}

void ClydeState::evade(Ghost& ghost, int x, int y)
{
	ghost.Move(x, y);
	//SetState to chase for powerpill wearoff?
}
void ClydeState::returnToBase(Ghost& ghost, int x, int y)
{
	Coord2 ghPos;
	ghPos.x = x;
	ghPos.y = y;
	ghost.SetPosition(ghPos);
	//return to chase when reaches house
}