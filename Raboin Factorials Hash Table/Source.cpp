//Eric Raboin - Recursive Factorial Program
#include <iostream>
using namespace std;

int factorial(int num)
{
	if (num <= 1)
		return 1.0;

	return num * factorial(num-1);
}

int main()
{
	int answer = factorial(5);
	cout << "Result: " << answer << endl;

	system("pause");
	return 0;
}


//Eric Raboin - Non-Recursive Factorial Program 
#include <iostream>
using namespace std;

int result = 1;
int nonRecursiveFactorial(int num)
{
	if (num >= 2)
		for (int cntr = 1; cntr <= num; cntr++)
			result = result * cntr;
	else
	{
		result = 1;
	}
	return result;
}

int main()
{
	cout << "Input number to run Non Recursive factorial program for: " << endl;
	int factorNum;
	cin >> factorNum;
	int answer = nonRecursiveFactorial(factorNum);
	cout << "Result: " << answer << endl;

	system("pause");
	return 0;
}

//Eric Raboin - Basic Hash Table

#include <iostream>
#include <string>

using namespace std;

const int row = 7;
const int col = 4;
string dataArray[row][col] =
{
	{ "Gary Smith",      "GarySmith@neit.edu",    "$15.00" },
	{ "Laila Kerniech",    "LailaKeniech@neit.edu",    "$30.00" },
	{ "Shawn Kemp",      "ShawnKemp@neit.edu",    "$23.50" },
	{ "Sarah Palin",       "SarahPalin@neit.edu",    "$110.00" },
	{ "Ray Connif",     "RayConnif@neit.edu",    "$0.00" },
	{ "Edmund Cortis",      "EdmundCortis@neit.edu",    "$50.00" },
	{ "John Matis",    "JohnMatis@neit.edu",    "$15.00" },

};

string dataHashed[135][4];

class Search {
public:
	int hashRoutine(string playerToSearch) {
		int sum = 0;
		int len = playerToSearch.length();
		for (int ndx = 0; ndx < len; ndx++) {
			int decVal = playerToSearch.at(ndx);
			sum = sum + decVal;
		}
		return sum;
	}

	int hash(string playerToSearch) {
		cout << "Searching for " << playerToSearch << " using hash method." << endl;

		int foundAtIndex = hashRoutine(playerToSearch);

		cout << "Player " << playerToSearch << " is found at index " << foundAtIndex;
		cout << " after 1 read." << endl;

		return foundAtIndex;

	}

	void displayRecordFromHashtable(int index) {
		cout << "Record = "
			+ dataHashed[index][0]
			+ ", "
			+ dataHashed[index][1]
			+ ", "
			+ dataHashed[index][2]
			+ ", "
			+ dataHashed[index][3]
			<< endl;
	}

};

void main(void) {
	Search *search = new Search();

	for (int ndx = 0; ndx < row; ndx++) {
		int generatedHashIndex = search->hashRoutine(dataArray[ndx][0]);
		cout << "generatedHashIndex=" << generatedHashIndex << endl;
		dataHashed[generatedHashIndex][0] = dataArray[ndx][0];
		dataHashed[generatedHashIndex][1] = dataArray[ndx][1];
		dataHashed[generatedHashIndex][2] = dataArray[ndx][2];
		dataHashed[generatedHashIndex][3] = dataArray[ndx][3];
	}

	int rowItWasFound = search->hash("Sarah Palin");
	search->displayRecordFromHashtable(rowItWasFound);
	system("pause");
}



