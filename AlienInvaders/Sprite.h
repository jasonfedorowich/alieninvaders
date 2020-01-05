#include "boxcollider.h"
#include "animation.h"
#include "gameobject.h"
#include "staticdisplayobject.h"
#include <string>

#pragma once
class spritebuilder;
enum spritestate;

class sprite : public gameobject
{
private:
	boxcollider* _boxcollider;
	animation* _animation;
	int health;
	int dmg;
	const char* on_end_file;
	std::vector<void*> _utilities;
	spritestate _spritestate;
public:
	friend class spritebuilder;

	sprite();
	virtual ~sprite();
	sprite(spritebuilder* builder);

	virtual void draw();
	boxcollider* get_collider();
	void set_health(int health);
	int get_health();
	bool take_damage(int);
	void remove_health(int damage);
	spritestate get_state();
	const char* get_on_end_file();
	std::vector<void*> get_utilities();
	int get_damage();
	staticdisplayobject* explode();

};

class spritebuilder : public gameobjectbuilder {
private:
	int health;
	animation* _animation;
	int dmg;
	const char* on_end_file;
	std::vector<void*> _utilities;
	
public:
	friend class sprite;
	spritebuilder();
	virtual ~spritebuilder();

	spritebuilder* set_health(float);
	spritebuilder* set_damage(float dmg);
	spritebuilder* set_animation(std::vector<std::string>);

	spritebuilder* add_utility(void*);
	spritebuilder* set_on_end(const char* file);
	sprite* build_player();
	sprite* build_computer();
};

enum spritestate {
	ALIVE = 1, 
	DEAD = 0
};