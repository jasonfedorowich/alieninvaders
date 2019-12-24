#pragma once
#include "controller.h"
class enemycontroller: public controller
{
public:
	enemycontroller();
	~enemycontroller();

	// Inherited via controller
	virtual void move_sprite(void*, void*) override;
	virtual void fire(void*, void*) override;
};

