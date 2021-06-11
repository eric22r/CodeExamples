#include "Compression.h"

//Function to create a new node for the tree
void Compression::CreateNode()
{
	//Create the nodes for charactrers and set initializations
	for (int i = 0; i < 128; i++)
	{
		node_array[i] = new compression_node;
		node_array[i]->id = i;
		node_array[i]->freq = 0;

	}
}

//Function to move through the tree determining 1s or 0s
void Compression::MoveThroughTree(node_ptr node, string code)
{
	//When it reaches the proper node both sides will be null, take that value
	if (node->left == NULL && node->right == NULL)
	{
		node->code = code;
	}
	//Keep Moving through the tree
	else
	{
		MoveThroughTree(node->left, code + '0');
		MoveThroughTree(node->right, code + '1');
	}
}

//Function to change binary into deciimal format
int Compression::BinaryToDecimal(string _input)
{
	int result = 0;
	for (int i = 0; i < _input.size(); i++)
	{
		result = result * 2 + _input[i] - '0';
	}
	return result;
}

//Function to change decimal format into binary
string Compression::DecimalToBinary(int _input)
{
	string temp = "";
	string result = "";

	while (_input)
	{
		temp += ('0' + _input % 2);
		_input /= 2;
	}
	result.append(8 - temp.size(), '0');

	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}

//Function to create the tree of nodes to encode / decode from
inline void Compression::CreateTree(string& _path, char _aCode)
{
	node_ptr current = root;
	//Travel through the tree and create nodes depending left = 0 and right = 1
	for (int i = 0; i < _path.size(); i++)
	{
		if (_path[i] == '0')
		{
			if (current->left == NULL)
				current->left = new compression_node;
			current = current->left;
		}
		else if (_path[i] == '1')
		{
			if (current->right == NULL)
				current->right = new compression_node;
			current = current->right;
		}
	}
	//Set the value of the node to the proper character
	current->id = _aCode;
}

//Create Compression and nodes based on files in and out
Compression::Compression(string _in, string _out)
{
	inFileName = _in;
	outFileName = _out;

	CreateNode();
}

//Sorts nodes by frequency of occurance in the file. This will make each file have its own tree based on the frequency of characters to that file
void Compression::PQCreate()
{
	inFile.open(inFileName, ios::in);
	inFile.get(id);
	while (!inFile.eof())
	{
		node_array[id]->freq++;
		inFile.get(id);
	}
	inFile.close();
	for (int i = 0; i < 128; i++)
	{
		if (node_array[i]->freq)
		{
			pq.push(node_array[i]);
		}
	}
}

void Compression::CreateCompressionTree()
{
	priority_queue<node_ptr, vector<node_ptr>, compare> temp(pq);
	while (temp.size() > 1)
	{
		//create the compression tree and set highest frequecy characher being node from bottom to top
		//Uses a stack of frequencies to pull from
		root = new compression_node;
		root->freq = 0;
		root->left = temp.top();
		root->freq += temp.top()->freq;
		temp.pop();
		root->right = temp.top();
		root->freq += temp.top()->freq;
		temp.pop();
		temp.push(root);
	}
}
//Moves through the tree and calculate the compression code
void Compression::CalculateCompressionAlgo()
{
	MoveThroughTree(root, "");
}
//Function that saves the code into the file
void Compression::SaveCode()
{
	inFile.open(inFileName, ios::in);
	outFile.open(outFileName, ios::out | ios::binary);
	string in = "";
	string stringValue = "";

	string* sPtr = &stringValue;
	in += (char)pq.size();
	priority_queue<node_ptr, vector<node_ptr>, compare> temp(pq);
	//If there is something to write
	while (!temp.empty())
	{
		//get all characters and their huffman codes for output
		node_ptr current = temp.top();
		in += current->id;
		stringValue.assign(127 - current->code.size(), '0'); 
		stringValue += '1';					
		stringValue.append(current->code);
		in += (char)BinaryToDecimal(stringValue.substr(0,8));
		for (int i = 0; i < 15; i++)
		{
			//cut into binary codes to convert into saving chars needed for compressed file
			stringValue = stringValue.substr(8);
			in += (char)BinaryToDecimal(stringValue.substr(0, 8));
		}
		temp.pop();
	}
	stringValue.clear();
	
	inFile.get(id);
	while (!inFile.eof())
	{
		//get the compression information
		stringValue += node_array[id]->code;
		while (stringValue.size() > 8)
		{
			//cut into binary codes to convert into saving chars needed for compressed file
			in += (char)BinaryToDecimal(stringValue.substr(0, 8));
			stringValue = stringValue.substr(8);
		}
		inFile.get(id);
	}
	int count = 8 - stringValue.size();
	if (stringValue.size() < 8)
	{
		//append to the last few codes to create the last byte of text
		stringValue.append(count, '0');
	}
	in += (char)BinaryToDecimal(stringValue);	
	in += (char)count;

	//Write the tree into the file and close the file for now
	outFile.write(in.c_str(), in.size());
	inFile.close();
	outFile.close();
}

void Compression::RecreateCompressionTree()
{
	//Opens the file and reads via reinterpret cast
	inFile.open(inFileName, ios::in | ios::binary);
	unsigned char size;
	inFile.read(reinterpret_cast<char*>(&size), 1);
	root = new compression_node;

	//Recreates the tree that was created when encoding for proper decoding
	for (int i = 0; i < size; i++)
	{
		char nodeValue;
		unsigned char nodeChar[16];
		inFile.read(&nodeValue, 1);
		inFile.read(reinterpret_cast<char*>(nodeChar), 16);

		string nodeValueString = "";

		for (int i = 0; i < 16; i++)
		{
			nodeValueString += DecimalToBinary(nodeChar[i]);
		}
		int j = 0;
		while (nodeValueString[j] == '0')
		{
			j++;
		}
		nodeValueString = nodeValueString.substr(j + 1);
		CreateTree(nodeValueString, nodeValue);
	}
	//Close File aftet cycling through and creating the tree
	inFile.close();

}

//Saves into file once decoded
void Compression::SaveFromDecoding()
{
	//Open the file declaring its in binary
	inFile.open(inFileName, ios::in | ios::binary);

	//Open the file it will be decoded and written to
	outFile.open(outFileName, ios::out);
	unsigned char size;

	//reinterpret cast to convert pointers between types
	inFile.read(reinterpret_cast<char*>(&size), 1);
	inFile.seekg(-1, ios::end);
	char startChar;
	inFile.read(&startChar, 1);
	inFile.seekg(1 + 17 * size, ios::beg);

	vector<unsigned char> text;
	unsigned char textSeg;
	inFile.read(reinterpret_cast<char*>(&textSeg), 1);

	while (!inFile.eof())
	{
		text.push_back(textSeg);
		inFile.read(reinterpret_cast<char*>(&textSeg), 1);
	}

	node_ptr current = root;
	string path;

	//Follows the path for decoding until both left and right are NULL (end of the tree - that value is the decoded character)
	for (int i = 0; i < text.size() - 1; i++)
	{
		path = DecimalToBinary(text[i]);
		if (i == text.size() - 2)
			path = path.substr(0, 8 - startChar);
		for (int j = 0; j < path.size(); j++)
		{
			if (path[j] == '0')
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}

			if (current->left == NULL && current->right == NULL)
			{
				//Write the char found to the output file
				outFile.put(current->id);
				current = root;
			}
		}
	}
		//Close the files when decompression is completed
		inFile.close();
		outFile.close();
	}
