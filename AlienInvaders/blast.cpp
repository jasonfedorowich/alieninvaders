#include "blast.h"
#include <exception>
#include "ship.h"
#include "staticdisplayfactory.h"

blast::blast(colliderbodybuilder* builder) : twodcolliderbody(builder)
{
	
}

blast::blast()
{
}


blast::~blast()
{
	
}

int blast::get_damage()
{
	return this->get_utility();
}

void blast::set_damage(int dmg)
{
	this->set_utility(dmg);
}

staticdisplayobject* blast::explode() {

	float x = this->get_x_position();
	float y = this->get_y_position();
	return staticdisplayfactory::create_explosion(x, y, this->get_size_x(), this->get_size_y(), 
		this->get_on_end_file());
}

