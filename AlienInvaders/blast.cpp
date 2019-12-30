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


staticdisplayobject* blast::explode() {

	float x = this->get_x_position();
	float y = this->get_y_position();
	return staticdisplayfactory::create_explosion(x, y, this->get_size_x(), this->get_size_y(), 
		this->get_on_end_file());
}

