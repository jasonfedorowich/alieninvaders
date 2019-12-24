#include "enemy.h"
#include "colliderfactory.h"


std::map<int, std::vector<const char*>>* enemy::_animations = new std::map<int, std::vector<const char*>>();

float enemy::enemy_speed = 5.0f;
float enemy::damage = 10.0f;

enemy::enemy(spritebuilder* builder) : sprite(builder)
{
  this->x_rate = rand() % 19 + (-9); 
  this->blast_file = "../resources/images/enemyblast1.png";
}


enemy::~enemy()
{
	
}

void enemy::move()
{
	this->increment_pos(this->x_rate, enemy::enemy_speed);
}

void enemy::delete_enemy_resouces()
{
	delete enemy::_animations;
}

twodcolliderbody* enemy::fire()
{
	return colliderfactory::create_2d_collider(this->get_x_position(), this->get_y_position(), this->get_damage(), this->blast_file);
}

void init_enemy_animations()
{

	std::vector<const char*> animationstrs;
	animationstrs.push_back("../resources/images/enemy1.png");
	animationstrs.push_back("../resources/images/enemy2.png");
	

	(*enemy::_animations)[1] = animationstrs;

}
