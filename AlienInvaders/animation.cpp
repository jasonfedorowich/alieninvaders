#include "animation.h"



animation::animation()
{
}


animation::~animation()
{
	while (!_bitmaps->empty()) {
		al_destroy_bitmap(_bitmaps->back()), _bitmaps->pop_back();
	}
	delete _bitmaps;
}


animation::animation(std::vector<ALLEGRO_BITMAP*>* bitmaps)
{
	this->_bitmaps = bitmaps;
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
		al_draw_bitmap((*_bitmaps)[position], x, y, 0);

		this->position = this->position + 1;
		if (position >= _bitmaps->size())
			position = 0;
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}
	

}

