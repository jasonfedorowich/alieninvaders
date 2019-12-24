#pragma once
#include "twodcolliderbody.h"
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "Sprite.h"


class blast : public twodcolliderbody
{
private:
	
public:

	blast(colliderbodybuilder*);

	blast();
	~blast();


	staticdisplayobject* explode() override;

	static float blast_speed;
	static float blast_size_x;
	static float blast_size_y;
	static float enemy_blast_speed;
	


};


