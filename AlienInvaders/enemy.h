#pragma once
#include "Sprite.h"
#include "animation.h"
#include <map>
#include "twodcolliderbody.h"
class enemy : public sprite
{
private:
	float x_rate;

public:
	enemy();
	enemy(spritebuilder* builder);
	virtual ~enemy();
	void move(float);

	void reverse_x_rate();

	twodcolliderbody* fire();

	static float enemy_speed;
	static float damage;

};

