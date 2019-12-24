#include "blast.h"
#include <exception>
#include "ship.h"
#include "staticdisplayfactory.h"

float blast::blast_speed = -10.0f;
float blast::blast_size_x = 64.0;
float blast::blast_size_y = 64.0;
//TODO make a variable
float blast::enemy_blast_speed = 7.0f;

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
	return staticdisplayfactory::create_explosion(x, y, blast::blast_size_x, blast::blast_size_y, "../resources/images/smallexplo1.png");
}

