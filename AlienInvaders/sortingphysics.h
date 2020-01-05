#pragma once
#include "physics.h"
class sortingphysics :
	public physics
{
public:
	sortingphysics();
	virtual ~sortingphysics();

	// Inherited via physics
	//virtual void* evaluate(void*, void*) override;

	// Inherited via physics
	virtual int evaluate(void*, void*, void*, void* action(void*, void*)) override;
};

