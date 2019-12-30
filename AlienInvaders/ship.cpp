#include "ship.h"
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/color.h"
#include <exception>
#include "colliderfactory.h"

//TODO i dont like the way i init this may have to look into this again


ship::ship(spritebuilder* builder) : sprite(builder)
{
	
}


ship::~ship()
{
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
	
	blasts.push_back(colliderfactory::create_2d_collider(x + 72, y, this->get_utility()));
	blasts.push_back(colliderfactory::create_2d_collider(x - 8, y, this->get_utility()));
	
	return blasts;
}

int ship::get_level()
{
	return 1;
}
