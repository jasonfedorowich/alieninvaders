#pragma once
#include "twodcolliderbody.h"
class heart :public twodcolliderbody
{
public:
	heart();
	heart(colliderbodybuilder*);
	virtual ~heart();

	int get_healing_power();
	void set_healing_power(int);

};

