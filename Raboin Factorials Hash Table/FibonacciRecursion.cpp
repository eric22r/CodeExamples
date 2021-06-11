#include<iostream> 

using namespace std;

int Fib(int n)
{
	if (n <= 2)
	{
		return n;
	}
	return Fib(n - 1) + Fib(n - 2);
}
int main()
{
	int input;

	cout << "Enter the number you would like to run the program for." << endl;

	cin >> input;

	for (int i = 0; i < input; i++)
	{
cout << "The Fibonacci number for " << i+1 << " is " << Fib(i) << "  " << endl;
	}
	system("pause");

	return 0;
}
