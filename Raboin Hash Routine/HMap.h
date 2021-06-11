#pragma once

#include "HNode.h"
class HMap
{
public:
	HMap(int tableSize);
	void add(int key, Player *data);
	Player* get(int key);
	~HMap();
	
private:
	int hash(string keyToHash);
	HNode *table;
	int tableSize;
};
