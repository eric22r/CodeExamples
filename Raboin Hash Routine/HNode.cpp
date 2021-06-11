#include "HNode.h"

//Constructors
HNode::HNode(int key, Player *value) :
	key(key),
	value(value)
{}

HNode::HNode() :
	key(0),
	value(nullptr)
{}
//Destructors
HNode::~HNode() {}
