#pragma once
#include <allegro5/allegro_primitives.h>
#include "staticdisplayobject.h"

class background : public staticdisplayobject
{
private:
	
public:
	background(staticdisplaybuilder*);
	background();
	virtual ~background();

	virtual void draw() override;

};

