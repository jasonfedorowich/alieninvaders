#pragma once
#include "physics.h"
class sortingphysics :
	public physics
{
public:
	sortingphysics();
	~sortingphysics();

	// Inherited via physics
	//virtual void* evaluate(void*, void*) override;

	// Inherited via physics
	virtual int evaluate(void*, void*, void*) override;
};

