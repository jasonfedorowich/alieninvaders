#pragma once
#include "Sprite.h"
#include "animation.h"
#include <map>
#include "twodcolliderbody.h"
class enemy : public sprite
{
private:
	float x_rate;
	const char* blast_file;

public:
	static std::map<int, std::vector<const char*>>* _animations;
	enemy();
	enemy(spritebuilder* builder);
	~enemy();
	void move();

	void delete_enemy_resouces();

	twodcolliderbody* fire();

	static float enemy_speed;
	static float damage;

};

void init_enemy_animations();