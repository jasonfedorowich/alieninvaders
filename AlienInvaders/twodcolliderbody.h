#include "boxcollider.h"
#include "gameobject.h"
#include "staticdisplayobject.h"

#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#pragma once
//TODO refactor we need to create a builder for this object
class colliderbodybuilder;

class twodcolliderbody : public gameobject
{
private:
	float x, y;
	boxcollider* _boxcollider;
	int damage;
	ALLEGRO_BITMAP* bitmap;
public:
	friend class colliderbodybuilder;
	twodcolliderbody();
	~twodcolliderbody();
	twodcolliderbody(colliderbodybuilder*);
	virtual staticdisplayobject* explode();
	
	virtual void draw();
	boxcollider* get_collider();

	int get_damage();
	void set_damage(int);
};


class colliderbodybuilder : public gameobjectbuilder{

private:
	int damage;
	const char* image;
public:
	colliderbodybuilder();
	~colliderbodybuilder();
	friend class twodcolliderbody;

	colliderbodybuilder* set_damage(int);
	colliderbodybuilder* set_image(const char*);

	twodcolliderbody* build_blast();

};
