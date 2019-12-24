#include "animation.h"



animation::animation()
{
}


animation::~animation()
{
	for (int i = 0; i < bitmaps.size(); i++)
		al_destroy_bitmap(bitmaps[i]);
}


animation::animation(std::vector<ALLEGRO_BITMAP*> bitmaps)
{
	this->bitmaps = bitmaps;
	this->position = 0;
}

void animation::set_position(float x, float y)
{
	this->x = x;
	this->y = y;
}

float animation::get_x_position()
{
	return this->x;
}

float animation::get_y_position()
{
	return this->y;
}

void animation::animate()
{
	try {
		al_draw_bitmap(bitmaps[position], x, y, 0);

		this->position = this->position + 1;
		if (position >= bitmaps.size())
			position = 0;
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}
	

}

