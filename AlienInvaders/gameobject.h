#include "boxcollider.h"

#pragma once
class gameobjectbuilder;
class gameobject
{
private:
	float x, y;
	float size_x, size_y;
	int layer;
public:
	friend class gameobjectbuilder;
	gameobject(gameobjectbuilder*);
	gameobject();
	virtual ~gameobject();

	float get_x_position();
	float get_y_position();
	float get_size_x();
	float get_size_y();

	void increment_y_pos(float);
	void increment_x_pos(float);
	void increment_pos(float, float);

	virtual void draw();

	void set_position(float, float);
	void set_y_position(float);
	void set_x_position(float);


	int get_sorting_layer();
};

class gameobjectbuilder {

private:
	float x, y;
	float size_x, size_y;
	int layer;
public:
	friend class gameobject;
	gameobject* build();
	virtual ~gameobjectbuilder();
	virtual gameobjectbuilder* sizex(float);
	virtual gameobjectbuilder* sizey(float);
	virtual gameobjectbuilder* pos_x(float);
	virtual gameobjectbuilder* pos_y(float);
	virtual gameobjectbuilder* sorting_layer(int);
	

};
