#include "physics.h"
#include <vector>
#include <map>
#include <string>

#pragma once
class physicsengine
{
private:
	std::map<std::string, physics*>* _physics;
public:
	physicsengine();
	~physicsengine();

	int evaluate_collisions(void* object1, void* object2, void* object3);
	int evaluate_sorting(void* object1, void* object2, void* object3);



};

