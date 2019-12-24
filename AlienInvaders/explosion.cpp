#include "explosion.h"
#include <exception>
#include "blast.h"

explosion::explosion()
{
}


explosion::~explosion()
{
}

explosion::explosion(staticdisplaybuilder* builder) : staticdisplayobject(builder)
{

}

void explosion::draw()
{
	float x = this->get_x_position();
	float y = this->get_y_position();

	x = x - this->get_factor_x() / 2;
	y = y - this->get_factor_y() / 2;

	al_draw_bitmap(this->get_bitmap(), x, y, 0);
	staticdisplayobject::draw(true);
}