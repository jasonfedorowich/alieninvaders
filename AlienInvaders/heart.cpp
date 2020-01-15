#include "heart.h"

heart::heart()
{
}

heart::heart(colliderbodybuilder* builder) : twodcolliderbody(builder)
{
}

heart::~heart()
{
}

int heart::get_healing_power()
{
	return this->get_utility();
}

void heart::set_healing_power(int healing_power)
{
	this->set_utility(healing_power);
}
