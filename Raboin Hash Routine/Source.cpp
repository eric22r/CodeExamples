#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <Windows.h>
#include "HMap.h"


using namespace std;

//Declare global variables
//Excel information
string junk;
string fullTag;

vector<vector<string>> Tags;

const static enum fileType { CSV, XML };

vector<Player> playerVect;
Player tempPlayer;
//Function to read the file and information stored
void readFile(string _file, fileType fType)
{
	ifstream inFile;
	inFile.open(_file);
	if (inFile.is_open())
	{
		cout << "File Opened..." << endl;
	}
	else
	{
		cout << "File was not able to be opened!" << endl;
	}

	string temp;
	int tags = 0;
	vector<string> inputs;
	string tempInput;

	switch (fType)
	{
	case CSV:
		while (temp.find("\n") == std::string::npos)	//Get amount of tags
		{
			getline(inFile, temp, ',');
			tags++;
		}
		inFile.clear();
		inFile.seekg(0);	//return to top of file

		while (!inFile.eof())
		{
			for (int i = 0; i < tags - 1; ++i)
			{
				getline(inFile, tempInput, ',');
				inputs.push_back(tempInput);
			}
			getline(inFile, tempInput, '\n');
			inputs.push_back(tempInput);

			Tags.push_back(inputs);
			inputs.clear();
		}
		Tags.pop_back();

		inFile.close();
		break;
	case XML:
		getline(inFile, temp, '<');
		getline(inFile, temp, '>');
		fullTag = temp;
		tags = -2;	// -2 Tags for the 2 tags that envelope all the others
		while (temp.find("/" + fullTag) == std::string::npos)
		{
			getline(inFile, temp, '\n');
			tags++;
		}

		inFile.clear();
		inFile.seekg(0);	//return to top of file

		getline(inFile, junk, '<');
		getline(inFile, tempInput, '>');

		for (int i = 0; i < tags; ++i)	//All other Tags
		{
			getline(inFile, junk, '<');
			getline(inFile, tempInput, '>');
			inputs.push_back(tempInput);
			getline(inFile, junk, '>');
		}

		Tags.push_back(inputs);
		inFile.clear();
		inFile.seekg(0);	//return to top of file

		while (!inFile.eof())	//Input all inputs in file
		{
			inputs.clear();
			getline(inFile, junk, '\n');
			for (int i = 0; i < tags; ++i)
			{
				getline(inFile, junk, '>');
				getline(inFile, tempInput, '<');
				inputs.push_back(tempInput);
				getline(inFile, junk, '\n');
			}
			Tags.push_back(inputs);
			getline(inFile, junk, '\n');
		}

		Tags.pop_back();
		inFile.close();
	}
}


int main()
{
	//Declare vars
	HMap map(2000);
	//Change to search key
	int keyToSearch = 2227;
	//Read file
	readFile("uniqueCSV.csv", CSV);

	//Creates the player and inserts into map
	for (int i = 0; i < Tags.size(); i++)
	{
		Player* insPlayer = new Player();
		insPlayer->count = Tags[i][0];
		insPlayer->port = Tags[i][1];
		insPlayer->citizenship = Tags[i][2];
		insPlayer->year = Tags[i][3];

		cout << "inserting player with key " << insPlayer->count << endl;
		map.add(atoi(insPlayer->count.c_str()), insPlayer);

	}



	//Output benchmark for hashmap
	cout << "Lookup time for key " << keyToSearch << " using hashmap: ";
	auto start = chrono::high_resolution_clock::now();
	map.get(keyToSearch);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << duration.count() << " microseconds" << endl;

	system("pause");
	//Output benchmark for linear search
	cout << "Lookup time for key " << keyToSearch << " using linear search: ";
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < Tags.size(); i++)
	{
		if (atoi(Tags[i][0].c_str()) == keyToSearch)
		{
			break;
		}
	}
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << duration.count() << " microseconds" << endl;



	system("pause");
	return 0;
}
