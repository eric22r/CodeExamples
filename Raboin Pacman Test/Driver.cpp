#include <iostream>
#include <windows.h>
#include "Ghost.h"
#include"State.h"
#include "Pacman.h"
#include "Timer.h"
#include <dos.h>
#include <sstream>
#include <string>
#include <time.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

enum class GameState
{
	INSTRUCTIONS,
	GAME,
	GAMEOVER,
};

void SetCoordinateXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
char pac_map[23][32];

char map[23][32] = {
	"+#############################+",
	"|P----------######-----------P|",
	"|-#########-######-##########-|",
	"|-#########-######-##########-|",
	"|----------P------------------|",
	"|-##-####-#-#########-####-##-|",
	"|-##-####-#-#########-##------|",
	"|-##-####-#-----P-----##-####-|",
	"|-----------###~~~###---------|",
	"|#-#####-##-#~~~~~~~#-##-#----|",
	"|#-#-----##-#~~~~~~~#-##----##|",
	"|#-#-###-##-#~~~~~~~#----##-##|",
	"|#-#-###-##-#########-##-##-##|",
	"|-----------------------------|",
	"|#-###-####-###-####-#########|",
	"|#-###-####-###-####-#########|",
	"|----------P------------------|",
	"|--#####-#########-##########-|",
	"|--#####-#########-##########-|",
	"|P-------#########-----------P|",
	"+#############################+"
};

void ShowMap()
{
	for (int i = 0; i < 23; i++) {
		printf("%s\n", map[i]);
	}
}

void gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(hStdout, position);
}




int main()
{
	Timer t;
	Timer blinkyGhostActionTime;
	Timer inkyGhostActionTime;
	Coord preMove;
	bool chase = true;
	int score = 0;
	int pinkyX = 10;
	int pinkyY = 12;
	Ghost Pinky(1,pinkyX, pinkyY);
	int inkyX = 8;
	int inkyY = 16;
	Coord2 inkyLoc;
	Ghost Inky(2, inkyX, inkyY);
	int blinkyX = 4;
	int blinkyY = 16;
	Coord2 blinkyLoc;
	Ghost Blinky(3, blinkyX, blinkyY);
	int clydeX = 4;
	int clydeY = 6;
	Ghost Clyde(4, clydeX, clydeY);

	Pacman *pacman = new Pacman(5);
	pacman->SetLives(1);
	blinkyLoc.x = blinkyX;
	blinkyLoc.y = blinkyY;
	inkyLoc.x = inkyX;
	inkyLoc.y = inkyY;

	Blinky.SetPosition(blinkyLoc);
	Inky.SetPosition(inkyLoc);
	SetCoordinateXY(Blinky.GetPosition().x, Blinky.GetPosition().y);
	SetCoordinateXY(Inky.GetPosition().x, Inky.GetPosition().y);
	std::system("cls");
	gotoxy(20, 10);
	std::cout << "WASD moves! You are pacman (C)";
	gotoxy(20, 11);
	std::cout << "Avoid the Ghosts ( I, B, L, N )";
	gotoxy(20, 12);
	std::cout << "Collect every cookie to win! ( - )";
	gotoxy(20, 13);
	std::cout << "Get the power pill to eat the ghosts! ( P )";
	gotoxy(20, 14);
	std::cout << "Press any key key to start!";
	system("pause");
	ShowMap();
	t.Start();
	inkyGhostActionTime.Start();
	blinkyGhostActionTime.Start();
	do {

		system("CLS");

		ShowMap();
		Coord pacLoc = pacman->GetPosition();
		Coord2 inkyLoc = Inky.GetPosition();
		Coord lastPosition = pacman->GetPosition();
		Pinky.chase(0, 1);
		
		if (pacman->GetPosition().x > inkyLoc.x)
		{
			if (inkyGhostActionTime.Elapsed() > .5)
			{
				if (chase)
				{
					if (map[inkyLoc.y][inkyLoc.x] != '#')
					Inky.chase(1, 0);
					else
					Inky.chase(0, 1);
				}
				else
				{
					if (map[inkyLoc.y][inkyLoc.x] != '#')
					Inky.evade(-1, 0);
					else
					Inky.evade(0, -1);
				}
				inkyGhostActionTime.Start();
			}
		}
		if (pacman->GetPosition().x < inkyLoc.x)
		{
			if (inkyGhostActionTime.Elapsed() > .5)
			{
				if (chase)
				{
					if (map[inkyLoc.y][inkyLoc.x] != '#')
					Inky.chase(-1, 0);
					else
						Inky.chase(0, 1);
				}
				else
				{
					if (map[inkyLoc.y][inkyLoc.x] != '#')
					Inky.evade(1, 0);
					else
						Inky.evade(0, -1);
				}
			}
		}
		if (pacman->GetPosition().y > inkyLoc.y)
		{
			if (inkyGhostActionTime.Elapsed() > .5)
			{
				if (chase)
				{
					if (map[inkyLoc.y][inkyLoc.x] != '#')
					Inky.chase(0, -1);
					else
						Inky.chase(1, 0);
				}
				else
				{
					if (map[inkyLoc.y][inkyLoc.x] != '#')
					Inky.evade(0, 1);
					else
						Inky.evade(-1, 0);
				}
				inkyGhostActionTime.Start();
			}
		}
		if (pacman->GetPosition().y < inkyLoc.y)
		{
			if (inkyGhostActionTime.Elapsed() > .5)
			{
				if (chase)
				{
					if (map[inkyLoc.y][inkyLoc.x] != '#')
					Inky.chase(0, -1);
					else
						Inky.chase(-1, 0);
				}
				else
				{
					if (map[inkyLoc.y][inkyLoc.x] != '#')
					Inky.evade(0, 1);
					else
						Inky.evade(1, 0);
				}
				inkyGhostActionTime.Start();
			}
		}
		if (inkyLoc.x > 29)
		{
			inkyLoc.x = 29;
		}
		if (inkyLoc.x < 1)
		{
			inkyLoc.x = 1;
		}
		if (inkyLoc.y > 19)
		{
			inkyLoc.y = 19;
		}
		if (inkyLoc.y < 1)
		{
			inkyLoc.y = 1;
		}



		if (pacman->GetPosition().x > blinkyLoc.x)
		{
			if (blinkyGhostActionTime.Elapsed() > .5)
			{
				if (chase)
				{
					if (map[blinkyLoc.y][blinkyLoc.x] != '#')
						Blinky.chase(1, 0);
					else
						Blinky.chase(0, 1);
				}
				else
				{
					if (map[blinkyLoc.y][blinkyLoc.x] != '#')
						Blinky.evade(-1, 0);
					else
						Blinky.evade(0, -1);
				}
				blinkyGhostActionTime.Start();
			}
		}
		if (pacman->GetPosition().x < blinkyLoc.x)
		{
			if (blinkyGhostActionTime.Elapsed() > .5)
			{
				if (chase)
				{
					if (map[blinkyLoc.y][blinkyLoc.x] != '#')
						Blinky.chase(-1, 0);
					else
						Blinky.chase(0, 1);
				}
				else
				{
					if (map[blinkyLoc.y][blinkyLoc.x] != '#')
						Blinky.evade(1, 0);
					else
						Blinky.evade(0, -1);
				}
				blinkyGhostActionTime.Start();
			}
		}
		if (pacman->GetPosition().y > blinkyLoc.y)
		{
			if (blinkyGhostActionTime.Elapsed() > .5)
			{
				if (chase)
				{
					if (map[blinkyLoc.y][blinkyLoc.x] != '#')
						Blinky.chase(0, -1);
					else
						Blinky.chase(1, 0);
				}
				else
				{
					if (map[blinkyLoc.y][blinkyLoc.x] != '#')
						Blinky.evade(0, 1);
					else
						Blinky.evade(-1, 0);
				}
				blinkyGhostActionTime.Start();
			}
		}
		if (pacman->GetPosition().y < blinkyLoc.y)
		{
			if (blinkyGhostActionTime.Elapsed() > .5)
			{
				if (chase)
				{
					if (map[blinkyLoc.y][blinkyLoc.x] != '#')
						Blinky.chase(0, -1);
					else
						Blinky.chase(-1, 0);
				}
				else
				{
					if (map[blinkyLoc.y][blinkyLoc.x] != '#')
						Blinky.evade(0, 1);
					else
						Blinky.evade(1, 0);
				}
				blinkyGhostActionTime.Start();
			}
		}
		if (blinkyLoc.x > 29)
		{
			blinkyLoc.x = 29;
		}
		if (blinkyLoc.x < 1)
		{
			blinkyLoc.x = 1;
		}
		if (blinkyLoc.y > 19)
		{
			blinkyLoc.y = 19;
		}
		if (blinkyLoc.y < 1)
		{
			blinkyLoc.y = 1;
		}








		Clyde.Move(0, 0);
		if (_kbhit() == true)
		{
			char key = _getch();
			preMove = pacLoc;
			if (key == 'd')
			{
				pacLoc.x += 1;
				preMove.x = pacLoc.x - 1;
			}
			else if (key == 'a')
			{
				pacLoc.x -= 1;
				preMove.x = pacLoc.x + 1;
			}
			else if (key == 'w')
			{
				pacLoc.y -= 1;
				preMove.y = pacLoc.y + 1;
			}
			else if (key == 's')
			{
				pacLoc.y += 1;
				preMove.y = pacLoc.y - 1;
			}
			if (pacLoc.x > 29)
			{
				pacLoc.x = 29;
			}
			if (pacLoc.x < 1)
			{
				pacLoc.x = 1;
			}
			if (pacLoc.y > 19)
			{
				pacLoc.y = 19;
			}
			if (pacLoc.y < 1)
			{
				pacLoc.y = 1;
			}
			if (map[pacLoc.y][pacLoc.x] != '#')
			pacman->SetPosition(pacLoc);
		}
		//if (t.Elapsed() >= 10)
		//{
		//	//chase = !chase;
		//	t.Start();
		//}

		if (map[pacman->GetPosition().y][pacman->GetPosition().x] == 'P')
		{
			map[pacman->GetPosition().y][pacman->GetPosition().x] = ' ';
			chase = false;
			t.Start();
			

		}
		if (t.Elapsed() >= 10 && !chase)
		{
			chase = true;
			t.End();
		}

		if (map[pacman->GetPosition().y][pacman->GetPosition().x] == '-')
		{
			map[pacman->GetPosition().y][pacman->GetPosition().x] = ' ';
			score++;
		}
		if (map[pacman->GetPosition().y][pacman->GetPosition().x] != '#')
		{
			SetCoordinateXY(pacman->GetPosition().x, pacman->GetPosition().y);
			cout << "C";
		}
		else
		{
			SetCoordinateXY(preMove.x, preMove.y);
			cout << "C";
		}
		if (map[Blinky.GetPosition().y][Blinky.GetPosition().x] != '#')
		{
			SetCoordinateXY(Blinky.GetPosition().x, Blinky.GetPosition().y);
			cout << "B";
		}
		if (map[Inky.GetPosition().y][Inky.GetPosition().x] != '#')
		{
			SetCoordinateXY(Inky.GetPosition().x, Inky.GetPosition().y);
			cout << "I";
		}

		if (Inky.GetPosition().x == pacman->GetPosition().x && Inky.GetPosition().y == pacman->GetPosition().y)
		{
			if (chase)
			{
				//pacman->SetLives(pacman->GetLives() - 1);
			}
			else
			{
				Coord2 ghPos;
				ghPos.x = 16;
				ghPos.y = 9;
				Inky.SetPosition(ghPos);
				//Inky.returnToBase(16,9);
			}
		}
		if (Blinky.GetPosition().x == pacman->GetPosition().x && Blinky.GetPosition().y == pacman->GetPosition().y)
		{
			if (chase)
			{
				pacman->SetLives(pacman->GetLives() - 1);
			}
			else
			{
				Coord2 ghPos;
				ghPos.x = 16;
				ghPos.y = 9;
				Blinky.SetPosition(ghPos);
				Blinky.returnToBase(9,16);
			}
		}

		

		//SetCoordinateXY(35, 2);
		gotoxy(35, 20);
		cout << "Score: " << endl;
		gotoxy(42, 20);
		cout << score << endl;
		gotoxy(34, 2);
		cout << "Ghost States: " << endl;
		gotoxy(34, 4);
		cout << "Blinky Chasing: " + chase << endl;
		gotoxy(34, 6);
		cout << "Inky Chasing: " + chase << endl;
		gotoxy(34, 8);
		cout << "Pinky Chasing: " + chase << endl;
		gotoxy(34, 10);
		cout << chase << endl;
	} while (pacman->GetLives() > 0 && score <= 241);

	system("CLS");
	if (score >= 241)
	{
		cout << "Congratulations! You have eaten all of the cookies!" << endl;
	}
	else
	{
		cout << "Sorry, you have lost all of your lives! Please play again!" << endl;
	}

	system("pause");
}