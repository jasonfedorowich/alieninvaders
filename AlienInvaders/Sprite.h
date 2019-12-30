#include "boxcollider.h"
#include "animation.h"
#include "gameobject.h"
#include "staticdisplayobject.h"
#include <string>

#pragma once
class spritebuilder;

class sprite : public gameobject
{
private:
	boxcollider* _boxcollider;
	animation* _animation;
	int health;
	int dmg;
	const char* on_end_file;
	void* utility;
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
	
	const char* get_on_end_file();
	void* get_utility();
	int get_damage();
	staticdisplayobject* explode();

};

class spritebuilder : public gameobjectbuilder {
private:
	int health;
	animation* _animation;
	int dmg;
	const char* on_end_file;
	void* utility;
	
public:
	friend class sprite;
	spritebuilder();
	~spritebuilder();

	spritebuilder* set_health(float);
	spritebuilder* set_damage(float dmg);
	spritebuilder* set_animation(std::vector<std::string>);

	spritebuilder* set_utility(void*);
	spritebuilder* set_on_end(const char* file);
	sprite* build_player();
	sprite* build_computer();
};

