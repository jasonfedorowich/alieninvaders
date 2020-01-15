#pragma once
#include "gameobject.h"
#include <allegro5/allegro_primitives.h>
#include <map>
#include <string>
//TODO builder for object
class staticdisplaybuilder;

class staticdisplayobject : public gameobject
{
private:
	bool drawn;
	ALLEGRO_BITMAP* bitmap;
	float factor_x, factor_y;
	std::map<int, ALLEGRO_BITMAP*> _animations;
public:
	friend class staticdisplaybuilder;
	staticdisplayobject();
	virtual ~staticdisplayobject();
	staticdisplayobject(staticdisplaybuilder*);

	void draw(bool);
	bool is_drawn();
	virtual void draw();
	virtual void draw(int);
	ALLEGRO_BITMAP* get_bitmap();
	float get_factor_x();
	float get_factor_y();
	std::map<int, ALLEGRO_BITMAP*> get_animations();
	void set_bitmap(ALLEGRO_BITMAP*);

};

class staticdisplaybuilder : public gameobjectbuilder {

private:
	bool drawn;
	ALLEGRO_BITMAP* _bitmap;
	float factor_x, factor_y;
	std::map<int, ALLEGRO_BITMAP*> _animations;
public:
	friend class staticdisplayobject;
	staticdisplaybuilder* is_drawn(bool);
	staticdisplaybuilder* image(const char*);
	staticdisplaybuilder* base_x_factor(float);
	staticdisplaybuilder* base_y_factor(float);
	staticdisplaybuilder* set_animation(std::map<int, std::string>);
	staticdisplayobject* build_explosion();
	staticdisplayobject* build_healthbar();
	staticdisplayobject* build_image();

};
