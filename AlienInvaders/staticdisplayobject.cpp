#include "staticdisplayobject.h"
#include <exception>
#include "explosion.h"
#include "background.h"
#include "healthbar.h"

staticdisplayobject::staticdisplayobject()
{
}


staticdisplayobject::~staticdisplayobject()
{
	//FIX this
	try {
		if (bitmap != NULL) {
			al_destroy_bitmap(bitmap);
		}
			
		for (auto it = this->_animations.begin(); it != this->_animations.end(); it++) {
			if (it->second != bitmap) {
				al_destroy_bitmap(it->second);
			}
		}
	}
	catch (std::exception e) {
		
	}
	

}

staticdisplayobject::staticdisplayobject(staticdisplaybuilder* builder) : gameobject(builder)
{
	this->drawn = builder->drawn;
	this->factor_x = builder->factor_x;
	this->factor_y = builder->factor_y;
	this->_animations = builder->_animations;
	this->bitmap = builder->_bitmap;
}

void staticdisplayobject::draw()
{
	al_draw_bitmap(this->get_bitmap(), this->get_x_position(), this->get_y_position(), 0);
}

void staticdisplayobject::draw(int i)
{
	this->set_bitmap(this->get_animations()[i]);
	staticdisplayobject::draw();
}

ALLEGRO_BITMAP* staticdisplayobject::get_bitmap()
{
	return this->bitmap;
}

float staticdisplayobject::get_factor_x()
{
	return this->factor_x;
}

float staticdisplayobject::get_factor_y()
{
	return this->factor_y;
}

std::map<int, ALLEGRO_BITMAP*> staticdisplayobject::get_animations()
{
	return this->_animations;
}

void staticdisplayobject::set_bitmap(ALLEGRO_BITMAP* _bitmap)
{
	this->bitmap = _bitmap;
}

void staticdisplayobject::draw(bool drawn)
{
	this->drawn = drawn;
}


bool staticdisplayobject::is_drawn()
{
	return this->drawn;
}

staticdisplaybuilder* staticdisplaybuilder::is_drawn(bool drawn)
{
	this->drawn = drawn;
	return this;
}

staticdisplaybuilder* staticdisplaybuilder::image(const char* img)
{
	ALLEGRO_BITMAP* bitmap = al_load_bitmap(img);
	if (!bitmap)
		throw std::exception("Failed to init bitmap");
	this->_bitmap = bitmap;
	return this;
}

staticdisplaybuilder* staticdisplaybuilder::base_x_factor(float x)
{
	this->factor_x = x;
	return this;
}

staticdisplaybuilder* staticdisplaybuilder::base_y_factor(float y)
{
	this->factor_y = y;
	return this;
}

staticdisplayobject* staticdisplaybuilder::build_explosion()
{
	return new explosion(this);
}

staticdisplayobject* staticdisplaybuilder::build_background()
{
	return new background(this);
}

staticdisplayobject* staticdisplaybuilder::build_healthbar()
{
	return new healthbar(this);
}

staticdisplayobject* staticdisplaybuilder::build_image()
{
	return new staticdisplayobject(this);
}

staticdisplaybuilder* staticdisplaybuilder::set_animation(std::map<int, std::string> _anims)
{
	
	std::map<int, std::string>::iterator it;
	std::map<int, ALLEGRO_BITMAP*> _bitmaps;
	ALLEGRO_BITMAP* bitmap;
	for (it = _anims.begin(); it != _anims.end(); it++) {
		bitmap = al_load_bitmap(it->second.c_str());
		if (!bitmap)
			throw std::exception("Failed to init spaceship bitmap");
		_bitmaps[it->first] = bitmap;
	}
	this->_animations = _bitmaps;
	return this;
}

