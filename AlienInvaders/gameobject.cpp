#include "gameobject.h"



gameobject::gameobject(gameobjectbuilder* builder)
{
	this->x = builder->x;
	this->y = builder->y;
	this->size_x = builder->size_x;
	this->size_y = builder->size_y;
	this->layer = builder->layer;
}

gameobject::gameobject()
{
}


gameobject::~gameobject()
{
}

float gameobject::get_x_position()
{
	return this->x;
}

float gameobject::get_y_position()
{
	return this->y;
}

float gameobject::get_size_x()
{
	return this->size_x;
}

float gameobject::get_size_y()
{
	return this->size_y;
}

void gameobject::increment_y_pos(float rate)
{
	this->y = this->y + rate;
}

void gameobject::increment_x_pos(float rate)
{
	this->x = this->x = rate;
}

void gameobject::increment_pos(float x_rate, float y_rate)
{
	this->x = this->x + x_rate;
	this->y = this->y + y_rate;
}

void gameobject::draw()
{
}


void gameobject::set_position(float x, float y)
{
	this->x = x;
	this->y = y;
}

void gameobject::set_y_position(float y)
{
	this->y = y;
}

void gameobject::set_x_position(float x)
{
	this->x = x;
}

int gameobject::get_sorting_layer()
{
	return this->layer;
}


gameobject* gameobjectbuilder::build()
{
	return new gameobject(this);
}

gameobjectbuilder::~gameobjectbuilder()
{
}

gameobjectbuilder* gameobjectbuilder::sizex(float x)
{
	this->size_x = x;
	return this;
}

gameobjectbuilder* gameobjectbuilder::sizey(float y)
{
	this->size_y = y;
	return this;
}

gameobjectbuilder* gameobjectbuilder::pos_x(float x)
{
	this->x = x;
	return this;
}

gameobjectbuilder* gameobjectbuilder::pos_y(float y)
{
	this->y = y;
	return this;
}

gameobjectbuilder* gameobjectbuilder::sorting_layer(int layer)
{
	this->layer = layer;
	return this;
}



