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
	~enemy();
	void move(float);

	void delete_enemy_resouces();

	twodcolliderbody* fire();

	static float enemy_speed;
	static float damage;

};

