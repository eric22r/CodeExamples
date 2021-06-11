#include <iostream>
#include "Compression.h"

using namespace std;

int main()
{
	//Make it so you dont need to comment and uncomment to run both parts of the program
	int option = 0;
	cout << "Please enter 1 for compressing a file and 2 to decompress a file. Thank you!" << endl;
	cin >> option;
	if (option == 1)
	{
		//For Compressing the file
		cout << "Compressing requested file into output." << endl;
		Compression com("NativeFile.txt", "CompressedFile.SABAN");
		com.PQCreate();
		com.CreateCompressionTree();
		cout << "Compressing tree created" << endl;
		com.CalculateCompressionAlgo();
		cout << "Tree saved into file" << endl;
		com.SaveCode();
		cout << "Compression Completed!" << endl;
	}
	if (option == 2)
	{
		//For Decompressing the file
		Compression decom("CompressedFile.SABAN", "DecompressedFile.txt");
		decom.RecreateCompressionTree();
		cout << "Tree Found! Recreating nodes..." << endl;
		decom.SaveFromDecoding();
		cout << "File properly extracted!" << endl;
	}
	else
	{
		cout << "Please enter a correct option, 1 for compression and 2 for decompression" << endl;
	}
	//End the program
	return 0;
}
