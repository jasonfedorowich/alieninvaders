#pragma once
#include "Sprite.h"
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "twodcolliderbody.h"
#include <map>


class ship : public sprite
{

private: 
	const char* blast_file;

public:
	static std::map<int, std::vector<const char*>>* _animations;
	ship();
	ship(spritebuilder*);
	~ship();

	void delete_ship_resouces();

	std::vector<twodcolliderbody*> fire();
	int get_level();


};

void init_ship_animations();



