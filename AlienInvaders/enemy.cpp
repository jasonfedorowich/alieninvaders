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


twodcolliderbody* enemy::fire()
{
	return colliderfactory::create_2d_collider(this->get_x_position(), this->get_y_position(), this->get_utility());
}
