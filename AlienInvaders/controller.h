#pragma once
class controller
{
public:
	controller();
	~controller();

	virtual void move_sprite(void*, float, float) = 0;
	virtual void fire(void*, void*) = 0;

};

