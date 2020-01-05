#include "twodcolliderbody.h"
#include <exception>
#include "blast.h"


twodcolliderbody::twodcolliderbody()
{
}


twodcolliderbody::~twodcolliderbody()
{
	al_destroy_bitmap(this->bitmap);
	delete _boxcollider;
}

twodcolliderbody::twodcolliderbody(colliderbodybuilder* builder) : gameobject(builder)
{
	this->_boxcollider = new boxcollider(this->get_size_x(), this->get_size_y());
	this->damage = builder->damage;
	this->on_end_file = builder->on_end;
	this->_invulnerable = builder->_invulnerable;

	ALLEGRO_BITMAP* bitmap = al_load_bitmap(builder->image);
	if (!bitmap)
		throw std::exception("Failed to init spaceship bitmap");
	this->bitmap = bitmap;
}

staticdisplayobject* twodcolliderbody::explode()
{
	return nullptr;
}


void twodcolliderbody::draw()
{
	try {
		float x = this->get_x_position();
		float y = this->get_y_position();

		al_draw_bitmap(bitmap, x, y, 0);
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}
	
}



boxcollider* twodcolliderbody::get_collider()
{
	_boxcollider->set_position(this->get_x_position(), this->get_y_position());
	return _boxcollider;
}

const char* twodcolliderbody::get_on_end_file()
{
	return this->on_end_file;
}

int twodcolliderbody::get_damage()
{
	return this->damage;
}

void twodcolliderbody::set_damage(int dmg)
{
	this->damage = dmg;
}

bool twodcolliderbody::is_invulerable()
{
	return _invulnerable;
}

colliderbodybuilder::colliderbodybuilder()
{
}

colliderbodybuilder::~colliderbodybuilder()
{
}

colliderbodybuilder* colliderbodybuilder::set_damage(int damage)
{
	this->damage = damage;
	return this;
}

colliderbodybuilder* colliderbodybuilder::set_image(const char* image)
{
	this->image = image;
	return this;
}

colliderbodybuilder* colliderbodybuilder::set_on_end(const char* img)
{
	this->on_end = img;
	return this;
}

colliderbodybuilder* colliderbodybuilder::invulnerability(bool invulnerable)
{
	this->_invulnerable = invulnerable;
	return this;
}

twodcolliderbody* colliderbodybuilder::build_blast()
{
	return new blast(this);
}
