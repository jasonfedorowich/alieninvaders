#pragma once
#include "controller.h"
class enemycontroller: public controller
{
public:
	enemycontroller();
	~enemycontroller();

	// Inherited via controller
	virtual void move_sprite(void*, float, float) override;
	virtual void fire(void*, void*) override;
};

