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
	virtual ~blast();


	staticdisplayobject* explode() override;
	


};


