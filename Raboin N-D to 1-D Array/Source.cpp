#include <iostream>
#include <array>
#include <chrono>

using namespace std;


int main()
{

    int arr[3][2] = { {1,4},{2,3},{3,1} };

    int sum = 0;

    chrono::steady_clock::time_point startTime;


    startTime = chrono::steady_clock::now();

    for (int row = 0, col = 0; row < 3;)
    {
        if (col < 2)
        {

            sum += arr[row][col];

            col++;

        }
        else
        {
            col = 0;

            row++;
        }
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    chrono::duration<double> timePassed = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);

    cout << "Time Elapsed = " << timePassed.count() / 1000 << " milliseconds\n\n" << endl;
    cout << "The sum of the 2D Array converted to 1D: " << endl;
    cout << sum << endl;

    return 0;
}
