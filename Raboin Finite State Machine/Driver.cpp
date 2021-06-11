#include <iostream>
#include <Windows.h>
#include "Car.h"
#include "CarStates.h"
using namespace std;
int main()
{
	cout << "Thank you for using the autonomous valet system.\n We will automatically park your vehicle for you without the risk of joyriding, \nand will leave a computerized log in your email. We hope you enjoy your day!" << endl;
	cout << "------------------------------------------------\nBEGIN LOG\n------------------------------------------------\n";
	//Start car in parked state
	Car Camry(1);
	Camry.accelerate(2000);//State increase
	Camry.accelerate(3000);//State increase
	Camry.decelerate(2000);//State decrease
	Camry.decelerate(4000);//State decrease
	cout << "\n Your car is now parked! Thank you for using the autonomous valet service!\n" << endl;
	Sleep(3000);
	cout << "\nRequesting car retrieval.....\nBeginning return log......" << endl;
	Camry.accelerate(2000);//State increase
	Camry.accelerate(3000);//State increase
	Camry.decelerate(2000);//State decrease
	Camry.decelerate(4000);//State decrease
	cout << "\n\n     We hope you found our service quick and effective! Enjoy your day!" << endl;
	cout << "------------------------------------------------\nEND LOG\n------------------------------------------------\n";
	system("pause");
}