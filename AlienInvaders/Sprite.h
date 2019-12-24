#include "boxcollider.h"
#include "animation.h"
#include "gameobject.h"
#include "staticdisplayobject.h"

#pragma once
class spritebuilder;

class sprite : public gameobject
{
private:
	boxcollider* _boxcollider;
	animation* _animation;
	int health;
	int dmg;
public:
	friend class spritebuilder;

	sprite();
	~sprite();
	sprite(spritebuilder* builder);

	virtual void draw();
	boxcollider* get_collider();
	void set_health(int health);
	int get_health();
	bool take_damage(int);
	void remove_health(int damage);




	int get_damage();
	staticdisplayobject* explode();

};

class spritebuilder : public gameobjectbuilder {
private:
	int health;
	animation* _animation;
	int dmg;
public:
	friend class sprite;
	spritebuilder();
	~spritebuilder();

	spritebuilder* set_health(float);
	spritebuilder* set_damage(float dmg);
	spritebuilder* set_animation(std::vector<const char*>);
	sprite* build_player();
	sprite* build_computer();
};

