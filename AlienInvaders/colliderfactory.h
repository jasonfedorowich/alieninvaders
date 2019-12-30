#include "twodcolliderbody.h"
#include "Sprite.h"
#pragma once
class colliderfactory
{
public:
	colliderfactory();
	~colliderfactory();
	static twodcolliderbody* create_2d_collider(float, float, void*);

};

