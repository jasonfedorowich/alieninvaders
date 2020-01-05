#include "Sprite.h"
#include "ship.h"
#include "enemy.h"
#include "staticdisplayfactory.h"

const char* SPRITE_EXPLOSION = "../resources/images/explosion.png";
int SPRITE_SIZE = 128;

sprite::sprite()
{
}


sprite::sprite(spritebuilder* builder) : gameobject(builder)
{
	this->health = builder->health;
	this->_animation = builder->_animation;
	this->_boxcollider = new boxcollider(this->get_size_x(), this->get_size_y());
	this->_utilities = builder->_utilities;
	this->on_end_file = builder->on_end_file;
	if (!_boxcollider)
		throw std::exception("Failed to create a new box collider");
	this->dmg = builder->dmg;
	this->_spritestate = spritestate::ALIVE;
}

sprite::~sprite()
{
	delete _boxcollider;
	delete _animation;
}


void sprite::draw()
{
	float x = this->get_x_position();
	float y = this->get_y_position();
	_animation->set_position(x, y);
	_animation->animate();
}


boxcollider* sprite::get_collider()
{
	_boxcollider->set_position(this->get_x_position(), this->get_y_position());
	return _boxcollider;
}

void sprite::set_health(int health)
{
	this->health = health;
}

int sprite::get_health()
{
	return this->health;
}
//TODO maybe fix this method

bool sprite::take_damage(int dmg)
{
	health -= dmg;
	if (health > 0)
		return true;
	this->_spritestate = spritestate::DEAD;
	return false;
}

void sprite::remove_health(int damage)
{
	this->health = this->health - damage;

	if (this->health < 0)
		this->health = 0;
}

spritestate sprite::get_state()
{
	return this->_spritestate;
}



const char* sprite::get_on_end_file()
{
	return this->on_end_file;
}

std::vector<void*> sprite::get_utilities()
{
	return _utilities;
}


int sprite::get_damage() {
	return this->dmg;
}

staticdisplayobject* sprite::explode()
{
	return staticdisplayfactory::create_explosion(this->get_x_position(),
		this->get_y_position(),
		this->get_size_x(), this->get_size_y(), this->get_on_end_file());
}


spritebuilder* spritebuilder::set_animation(std::vector<std::string> bitmapstrs)
{
	std::vector<ALLEGRO_BITMAP*>* bitmaps = new std::vector<ALLEGRO_BITMAP*>();

	for (auto str : bitmapstrs) {
		ALLEGRO_BITMAP* bitmap = al_load_bitmap(str.c_str());
		if (!bitmap)
			throw std::exception("Failed to init spaceship bitmap");
		bitmaps->push_back(bitmap);
	}
	this->_animation = new animation(bitmaps);
	
	if (!_animation)
		throw std::exception("Failed to create animation");

	return this;
}

spritebuilder* spritebuilder::add_utility(void* utility)
{
	_utilities.push_back(utility);
	return this;
}

spritebuilder* spritebuilder::set_on_end(const char* file)
{
	this->on_end_file = file;
	return this;
}


sprite* spritebuilder::build_player()
{
	return new ship(this);
}

sprite* spritebuilder::build_computer()
{
	return new enemy(this);
}


spritebuilder::spritebuilder()
{
}

spritebuilder::~spritebuilder()
{
}

spritebuilder* spritebuilder::set_health(float health)
{
	this->health = health;
	return this;
}


spritebuilder* spritebuilder::set_damage(float dmg) {
	this->dmg = dmg;
	return this;
}
