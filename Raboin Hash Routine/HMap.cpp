#include "HMap.h"

HMap::HMap(int tableSize) :
	table(nullptr),
	tableSize(tableSize)
{
	this->table = new HNode[tableSize];
}
//Add information to hash map
void HMap::add(int key, Player *data)
{
	int hashKey = hash(to_string(key));

	table[hashKey].bucket.push_back(new HNode(key, data));
}
//Get information from hash map
Player* HMap::get(int key)
{
	HNode bucket = table[hash(to_string(key))];

	if (bucket.bucket.size() > 1)
	{
		//scan bucket to find correct key
		for (int i = 0; i < bucket.bucket.size(); i++)
		{
			if (bucket.bucket[i]->key == key)
			{
				return bucket.bucket[i]->value;
			}
		}
	}
	else if (bucket.bucket.size() == 1)
	{
		//only one result, return it
		return bucket.bucket[0]->value;
	}
	else
	{
		//no results, return nullptr
		return nullptr;
	}

}
//Create hash key
int HMap::hash(string keyToHash)
{
	int sum = 0;
	for (int i = 0; i < keyToHash.size(); i++)
	{
		sum += keyToHash[i] * i;
	}

	return sum % tableSize;
}
//Destructor
HMap::~HMap() {}
