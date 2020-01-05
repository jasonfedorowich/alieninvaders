#include "enemy.h"
#include "colliderfactory.h"



float enemy::enemy_speed = 5.0f;

enemy::enemy(spritebuilder* builder) : sprite(builder)
{
  this->x_rate = rand() % 19 + (-9); 

}


enemy::~enemy()
{
	
}

void enemy::move(float speed)
{
	this->increment_pos(this->x_rate, speed);
}

void enemy::reverse_x_rate()
{
	this->x_rate = -(this->x_rate);
	//this->increment_x_pos(this->x_rate);
}


twodcolliderbody* enemy::fire()
{
	return colliderfactory::create_2d_collider(this->get_x_position() + 30, this->get_y_position() + 70, this->get_utilities()[0]);
}
