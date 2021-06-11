#include <iostream>					
#include <vector>					
#include <string>					
#include <algorithm>				
#include <time.h>					
#include <math.h>					
#include <chrono>

//Definitions to be altered to adjust complexity of the code.
#define popSize			144
#define chromosomeNum	popSize
#define partySize		4
#define maxIterations	30000
#define elitismRate		0.1f
#define mutationRate	.02f
#define mutation		RAND_MAX * mutationRate


using namespace std;


//Struct to keep a vector of ints for the chromosome and the fitness score of the member
struct member
{
	vector<int> chromosome;
	int fitness;
};

vector<member> children;

int targetSize = popSize;
int issues;

//Create the population to begin testing and calculation fitness
void CreatePopulation(member &memb)
{
	memb.fitness = 0;

	for (int j = 0; j < targetSize; j++)
	{
		memb.chromosome.push_back(((rand() % partySize) + 1));
	}
}

    //Where the calculation for each chromomes fitness occurs
	void FitnessCalculation(member &memb)
	{
		int issues = 0;
		for (int j = 0; j < memb.chromosome.size() - 2; j++)
		{

			if ((memb.chromosome[j] + memb.chromosome[j + 1]) - memb.chromosome[j + 2] == memb.chromosome[j])
			{
				issues++;
			}
		}
		memb.fitness = issues;
	}

	bool fitness_sort(member x, member y)
	{
		return (x.fitness < y.fitness);
	}

	//Sort population in terms of fitness for selection
	inline void fitnessSort(vector<member> &members)
	{
		sort(members.begin(), members.end(), fitness_sort);
	}

	//Function to mutate if called
	void Mutation(vector<member> &pop)
	{

		for (int x = 0; x < chromosomeNum; x++)
		{

			int randPos = rand() % chromosomeNum;
			if(pop[x].chromosome[randPos] == pop[x].chromosome[(randPos + 1)%popSize])
				pop[x].chromosome[randPos] = rand() % partySize + 1;
		}
	}

	void Crossover(vector<member> &pop)
	{
		//Multiply by the elitism rate to account for most fit sections -- Does elitism here
		for (int i = pop.size() * elitismRate * 2; i < pop.size() - 1; i++)
		{
			for (int x = 0; x < chromosomeNum / partySize; x += partySize)
			{
				//Is this section good
				if (pop[i].chromosome[x] != pop[i].chromosome[x + 1] &&
					pop[i].chromosome[x + 1] != pop[i].chromosome[x + 2] &&
					pop[i].chromosome[x + 2] != pop[i].chromosome[x + 3])
				{
					//leave it alone
				}
				//If not then crossover
				else
				{
					pop[i].chromosome[x] = pop[i + 1].chromosome[x];
					pop[i].chromosome[x+1] = pop[i + 1].chromosome[x+1];
					pop[i].chromosome[x+2] = pop[i + 1].chromosome[x+2];
					pop[i].chromosome[x+3] = pop[i + 1].chromosome[x+3];
				}
				//Check to see if mutates
			}if (rand() < mutation)
				Mutation(pop);
		}
	}

	//Display the chromosome in easy to read format along with current generation and fitness score
	void displayResult(member &_population, int generation = 0)
	{
		system("cls");//Clear screen to reduce scrolling
		cout << "Generation: " << generation << endl;
		member display;
		display = _population;
		string space = "";
		int newLineCounter = 1;
		//Formats the output so its easier to read. The modulus amount can be adjusted to change the displayed grouping amounts
			for (int j = 0; j < targetSize; j++)
			{
				if (j % 4 == 3)
				{
					newLineCounter++;
					if(newLineCounter < 10)
					cout << to_string(display.chromosome[j]) + "    ";
					else
					{
						cout << to_string(display.chromosome[j]) + "\n\n";
						newLineCounter = 1;
					}
					
				}
				else
				{
					cout << to_string(display.chromosome[j]) + space;
				}
				
			}
		cout << endl;
		cout << "Fitness Score: " << display.fitness << endl;
		
		
	}
	//Swap function if needed
	inline void swap(member *&childrenA,
		member *&childrenB)
	{
		member *temp = childrenA; 
		childrenA = childrenB; 
		childrenB = temp;
	}

	int main()
	{
		srand(unsigned(time(NULL)));

		//Initialize population with members
		for (int i = 0; i < popSize; i++)
		{
			member new_member;
			CreatePopulation(new_member);
			FitnessCalculation(new_member);
			children.push_back(new_member);
		}
		//Cycle through until max Iterations are met or a solution is found
		for (int i = 0; i < maxIterations; i++)
		{
			displayResult(children[0], i);
			fitnessSort(children);
			if (children[0].fitness == 0)
			{
				FitnessCalculation(children[0]);
				displayResult(children[0], i);
				break;
			}
			//Crossover if solution is not found
			Crossover(children);

			//Recalculate fitness after crossover and potential mutation 
			for (int j = 0; j < popSize; j++)
				FitnessCalculation(children[j]);

		}
		//Allow user to view the output solution
			system("pause");
	}