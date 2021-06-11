#ifndef COMRESSION_H
#define COMPRESSION_H
#include <string>
#include <queue>
#include <vector>
#include <fstream>


using namespace std;
//Struct for creating the individual nodes
struct compression_node
{
	char id;
	int freq;
	string code;
	compression_node* left;
	compression_node* right;
	compression_node()
	{
		//constructor
		left = right = NULL;
	}
};

typedef compression_node* node_ptr;

//Main class for the program
class Compression
{
protected:
	node_ptr node_array[128];
	fstream inFile;
	fstream outFile;
	node_ptr child;
	node_ptr parent;
	node_ptr root;
	char id;
	string inFileName;
	string outFileName;
	class compare
	{
	public:
		bool operator()(const node_ptr& c1, const node_ptr& c2) const
		{
			return c1->freq > c2->freq;
		}
	};
	//Functions used within other functions
	priority_queue<node_ptr, vector<node_ptr>, compare> pq;	
	void CreateNode();
	void MoveThroughTree(node_ptr, string);	
	int BinaryToDecimal(string);
	string DecimalToBinary(int);
	inline void CreateTree(string&, char);
	//Functions to be called in main function
public:
	Compression(string, string);
	void PQCreate();
	void CreateCompressionTree();
	void CalculateCompressionAlgo();
	void SaveCode();
	void SaveFromDecoding();
	void RecreateCompressionTree();
};

#endif
