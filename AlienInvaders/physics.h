#include <vector>
#include "gameobject.h"
#pragma once
class physics
{
private:

public:
	physics();
	~physics();
	//TODO switch to varags with indexing
	virtual int evaluate(void*, void*, void*) = 0;
	
	//template<class T, class U, class V>
	//T evaluate(U*, V*) = 0;
};

