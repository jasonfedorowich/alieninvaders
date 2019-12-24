#include "ship.h"
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/color.h"
#include <exception>
#include "colliderfactory.h"

//TODO i dont like the way i init this may have to look into this again
std::map<int, std::vector<const char*>>* ship::_animations = new std::map<int, std::vector<const char*>>();


ship::ship(spritebuilder* builder) : sprite(builder)
{
	this->blast_file = "../resources/images/blastl1.png";
}


ship::~ship()
{
	delete ship::_animations;
	//TODO free(this_.blast_file);
}

void ship::delete_ship_resouces()
{
}



std::vector<twodcolliderbody*> ship::fire()
{
	float x = this->get_x_position();
	float y = this->get_y_position() + 10;

	std::vector<twodcolliderbody*> blasts;

	blasts.push_back(colliderfactory::create_2d_collider(x + 72, y, this->get_damage(), this->blast_file));
	blasts.push_back(colliderfactory::create_2d_collider(x - 8, y, this->get_damage(), this->blast_file));

	return blasts;
}

int ship::get_level()
{
	return 1;
}

//TODO change this made like enum or something
void init_ship_animations()
{
	
	
	std::vector<const char*> animationstrs;
	animationstrs.push_back("../resources/images/ship1.png");
	animationstrs.push_back("../resources/images/ship2.png");
	animationstrs.push_back("../resources/images/ship3.png");

	
	(*ship::_animations)[1] = animationstrs;
	
}
