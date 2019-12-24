#pragma once
#include "gameobject.h"
#include <allegro5/allegro_primitives.h>
//TODO builder for object
class staticdisplaybuilder;

class staticdisplayobject : public gameobject
{
private:
	bool drawn;
	ALLEGRO_BITMAP* bitmap;
	float factor_x, factor_y;

public:
	friend class staticdisplaybuilder;
	staticdisplayobject();
	~staticdisplayobject();
	staticdisplayobject(staticdisplaybuilder*);

	void draw(bool);
	bool is_drawn();
	virtual void draw();
	ALLEGRO_BITMAP* get_bitmap();
	float get_factor_x();
	float get_factor_y();

};

class staticdisplaybuilder : public gameobjectbuilder {

private:
	bool drawn;
	const char* img;
	float factor_x, factor_y;
public:
	friend class staticdisplayobject;
	staticdisplaybuilder* is_drawn(bool);
	staticdisplaybuilder* image(const char*);
	staticdisplaybuilder* base_x_factor(float);
	staticdisplaybuilder* base_y_factor(float);
	staticdisplayobject* build_explosion();
	staticdisplayobject* build_background();
};
