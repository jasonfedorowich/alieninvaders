#pragma once
#include "physics.h"
class bouncingphysics : public physics {
	// Inherited via physics
	bouncingphysics(void* action(void*));
	virtual ~bouncingphysics();
	virtual int evaluate(void*, void*, void*, void* action(void*, void*)) override;
};


