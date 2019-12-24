#include "staticdisplayobject.h"
#include <exception>
#include "explosion.h"
#include "background.h"


staticdisplayobject::staticdisplayobject()
{
}


staticdisplayobject::~staticdisplayobject()
{
	//FIX this
	al_destroy_bitmap(bitmap);
}

staticdisplayobject::staticdisplayobject(staticdisplaybuilder* builder) : gameobject(builder)
{
	this->drawn = builder->drawn;
	this->factor_x = builder->factor_x;
	this->factor_y = builder->factor_y;

	ALLEGRO_BITMAP* bitmap = al_load_bitmap(builder->img);
	if (!bitmap)
		throw std::exception("Failed to init bitmap");
	this->bitmap = bitmap;
}

void staticdisplayobject::draw()
{
	al_draw_bitmap(this->get_bitmap(), this->get_x_position(), this->get_y_position(), 0);
}

ALLEGRO_BITMAP* staticdisplayobject::get_bitmap()
{
	return this->bitmap;
}

float staticdisplayobject::get_factor_x()
{
	return this->factor_x;
}

float staticdisplayobject::get_factor_y()
{
	return this->factor_y;
}

void staticdisplayobject::draw(bool drawn)
{
	this->drawn = drawn;
}


bool staticdisplayobject::is_drawn()
{
	return this->drawn;
}

staticdisplaybuilder* staticdisplaybuilder::is_drawn(bool drawn)
{
	this->drawn = drawn;
	return this;
}

staticdisplaybuilder* staticdisplaybuilder::image(const char* img)
{
	this->img = img;
	return this;
}

staticdisplaybuilder* staticdisplaybuilder::base_x_factor(float x)
{
	this->factor_x = x;
	return this;
}

staticdisplaybuilder* staticdisplaybuilder::base_y_factor(float y)
{
	this->factor_y = y;
	return this;
}

staticdisplayobject* staticdisplaybuilder::build_explosion()
{
	return new explosion(this);
}

staticdisplayobject* staticdisplaybuilder::build_background()
{
	return new background(this);
}

