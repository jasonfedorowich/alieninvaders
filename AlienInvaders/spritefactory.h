#include "Sprite.h"
#pragma once
class spritefactory
{
public:
	spritefactory();
	~spritefactory();

	static sprite* create_generic_enemy(int);
};

