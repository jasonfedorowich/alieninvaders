#include "boxcollider.h"
#include <iostream>



boxcollider::boxcollider()
{
}


boxcollider::~boxcollider()
{
}

boxcollider::boxcollider(float width, float height)
{
	this->height = height;
	this->width = width;
	this->x = 0.0;
	this->y = 0.0;
}

boxcollider::boxcollider(float width, float height, float x, float y)
{
	this->height = height;
	this->width = width;
	set_position(x, y);
}



void boxcollider::set_position(float x, float y)
{
	this->x = x;
	this->y = y;
}

float boxcollider::get_x_position()
{
	return x;
}

float boxcollider::get_y_position()
{
	return y;
}

float boxcollider::get_height()
{
	return height;
}

float boxcollider::get_width()
{
	return width;
}

bool is_collision(boxcollider* box1, boxcollider* box2)
{
	float box1_x = box1->get_x_position();
	float box1_y = box1->get_y_position();
	float width_box1 = box1->get_width();
	float height_box1 = box1->get_height();

	float box2_x = box2->get_x_position();
	float box2_y = box2->get_y_position();
	float width_box2 = box2->get_width();
	float height_box2 = box2->get_height();

	if ((box1_x > box2_x + width_box2 - 1) || // is b1 on the right side of b2?
		(box1_y > box2_y + height_box2 - 1) || // is b1 under b2?
		(box2_x > box1_x + width_box1 - 1) || // is b2 on the right side of b1?
		(box2_y > box1_y + height_box1 - 1))   // is b2 under b1?
	{
		return false;
	}
	return true;
}

bool is_collision(int _x, int _y, boxcollider* _box)
{
	float box_x = _box->get_x_position();
	float box_y = _box->get_y_position();
	float width = _box->get_width();
	float height = _box->get_height();

	if ((_x > box_x + width ) ||
		(_y > box_y + height)||
		(box_x > _x )||
		(box_y > _y)) {
		return false;
	}


	return true;
}
