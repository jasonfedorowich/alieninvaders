#include "physicsengine.h"
#include "collisionphysics.h"
#include "sortingphysics.h"
#include <iostream>


physicsengine::physicsengine()
{
	std::map<std::string, physics*>* _physics = new std::map<std::string, physics*>();
	(*_physics)["collision"] = new collisionphysics();
	(*_physics)["sorting"] = new sortingphysics();
	this->_physics = _physics;
	
}


physicsengine::~physicsengine()
{
	delete _physics;
}



int physicsengine::evaluate_collisions(void* object1, void* object2, void* object3, void* action(void*, void*))
{
	return (*_physics)["collision"]->evaluate(object1, object2, object3, action);
}

int physicsengine::evaluate_sorting(void* object1, void* object2, void* object3, void* action(void*, void*))
{
	return (*_physics)["sorting"]->evaluate(object1, object2, object3, action);
}
