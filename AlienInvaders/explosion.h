#pragma once
#include "staticdisplayobject.h"
#include <allegro5/allegro_primitives.h>
class explosion : public staticdisplayobject
{
private:
	
public:
	explosion();
	virtual ~explosion();
	explosion(staticdisplaybuilder*);

	// Inherited via staticgameobject
	virtual void draw() override;
};

