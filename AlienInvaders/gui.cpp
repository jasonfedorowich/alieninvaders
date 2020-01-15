#include "gui.h"
#include <allegro5/allegro_ttf.h>
#include <iostream>

std::vector<gui::button*>* gui::mouse_event::_buttons = new std::vector<gui::button*>();

void gui::button::update(mouse_event_type _buttonstate, mouse_event* _event)
{
	this->_buttonstate = _buttonstate;
	_listeners[_buttonstate]->_event_(_event, _buttonstate);
	notify();
	
}

boxcollider* gui::button::get_collider()
{
	return this->_boxcollider;
}

void gui::button::notify()
{
	
}

gui::button::button()
{
}

gui::button::button(buttonbuilder* builder)
{
	boxcollider* _boxcollider = new boxcollider(builder->_size_x, builder->_size_y, builder->_x, builder->_y);
	this->_size_x = builder->_size_x;
	this->_size_y = builder->_size_y;
	this->_boxcollider = _boxcollider;
	this->_bitmap = builder->_bitmap;
	this->_font = builder->_font;
	this->_text = builder->_text;
	this->_x = builder->_x;
	this->_y = builder->_y;
	this->_color = builder->_color;
	mouse_event::register_(this);
	this->_buttonstate = mouse_event_type::NONE;
}

gui::button::~button()
{
	if(_bitmap)
		al_destroy_bitmap(_bitmap);
	if (_font)
		al_destroy_font(this->_font);
	button_listener* _listener;

	for (auto it = _listeners.begin(); it != _listeners.end(); it++) {
		_listener = (*it).second;
		delete _listener;
	}

	delete _boxcollider;
	mouse_event::unregister_(this);
}

void gui::button::add_listener(void* action(void*, void*), mouse_event_type _event_type)
{
	gui::button_listener* _listener = new gui::button_listener(this, action);
	_listeners[_event_type] = _listener;
}


void gui::button::draw()
{
	if (this->_bitmap != NULL)
		al_draw_bitmap(this->_bitmap, this->_x, this->_y, 0);

	else {
		al_draw_text(this->_font, this->_color, this->_x, this->_y, 0, this->_text);
		//std::cout << _size_x - _x;
		//std::cout << _size_y - _y;
		//al_draw_rectangle(this->_x, this->_y, this->_size_x, this->_size_y, this->_color, 0);
		//al_draw_line(this->_x, this->_y, (this->_x + this->_size_x), this->_y, this->_color, 0);
		//al_draw_line(this->_x, (this->_y + this->_size_y), (this->_x + this->_size_x), (this->_y + this->_size_y), this->_color, 0);
		//al_draw_line(this->_x, this->_y, this->_x, (this->_y + this->_size_y), _color, 0);
		//al_draw_line((this->_x + this->_size_x), this->_y, (this->_x + this->_size_x), (this->_y + this->_size_y), _color, 0);
	}
		
	if (this->_buttonstate == gui::mouse_event_type::MOUSE_DOWN) {
		al_draw_rectangle(this->_x, this->_y, (this->_x + this->_size_x), (this->_y + this->_size_y), this->_color, 0);
	}
}


void gui::button_listener::_event_(mouse_event* _event, mouse_event_type _type)
{
	_action(_event, &_type);
}

gui::button_listener::button_listener(button* _button, void* action(void*, void*))
{
	this->_button = _button;
	this->_action = action;

}


gui::button_listener::button_listener()
{
}

gui::button_listener::~button_listener()
{
}

//
//
//gui::mouse_down_listener::mouse_down_listener(button* _button, void* action(void*, void*)) : button_listener(_button, action)
//{
//	mouse_event::add_listener(this, mouse_event_type::MOUSE_DOWN);
//
//}
//
//gui::mouse_down_listener::mouse_down_listener()
//{
//
//}
//
//gui::mouse_down_listener::~mouse_down_listener()
//{
//}
//
//
//
//gui::mouse_up_listener::mouse_up_listener(button* _button, void* action(void*, void*)) : button_listener(_button, action)
//{
//	mouse_event::add_listener(this, mouse_event_type::MOUSE_UP);
//
//}
//
//gui::mouse_up_listener::mouse_up_listener()
//{
//}
//
//gui::mouse_up_listener::~mouse_up_listener()
//{
//}

gui::mouse_event::mouse_event(int x, int y, mouse_event_type _event)
{
	
	boxcollider* _collider;
	button* _button;
	for (int i = 0; i < _buttons->size(); i++) {
		_button = (*_buttons)[i];
		_collider = (*_buttons)[i]->get_collider();
		if (is_collision(x, y, _collider)) {
			_button->update(_event, this);
			break;
		}

	}
}

gui::mouse_event::~mouse_event()
{
}

void gui::mouse_event::register_(button* _button)
{
	mouse_event::_buttons->push_back(_button);

}

void gui::mouse_event::unregister_(button* _button)
{
	for (int i = gui::mouse_event::_buttons->size() - 1; i >= 0; i--) {
		if ((*gui::mouse_event::_buttons)[i] == _button)
			gui::mouse_event::_buttons->erase(gui::mouse_event::_buttons->begin() + i);
	}
}

void gui::mouse_event::delete_resources()
{
	for (int i = _buttons->size() - 1; i > 0; i--) {
		_buttons->erase(_buttons->begin() + i);
	}
	delete _buttons;
}

gui::buttonbuilder::buttonbuilder()
{
}

gui::buttonbuilder::~buttonbuilder()
{
}

gui::buttonbuilder* gui::buttonbuilder::image(const char* img)
{
	ALLEGRO_BITMAP* bitmap = al_load_bitmap(img);
	if (!bitmap)
		throw std::exception("Failed to init bitmap");
	this->_bitmap = bitmap;
	return this;
}

gui::buttonbuilder* gui::buttonbuilder::text(const char* text, const char* font_file, int size)
{
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT* font = al_load_ttf_font(font_file, size, 0);
	if (!font)
		throw std::exception("Failed to init font");
	this->_font = font;
	this->_text = text;
	this->_size_x = al_get_text_width(_font, _text);
	this->_size_y = al_get_font_line_height(_font);
	return this;
}

gui::buttonbuilder* gui::buttonbuilder::color(int r, int g, int b)
{
	ALLEGRO_COLOR _color = al_map_rgb(r, g, b);
	this->_color = _color;
	return this;
}

gui::buttonbuilder* gui::buttonbuilder::set_x(int _int)
{
	this->_x = _int;
	return this;
}

gui::buttonbuilder* gui::buttonbuilder::set_y(int _int)
{
	this->_y = _int;
	return this;
}

gui::buttonbuilder* gui::buttonbuilder::size_x(int _int)
{
	this->_size_x = _int;
	return this;
}

gui::buttonbuilder* gui::buttonbuilder::size_y(int _int)
{
	this->_size_y = _int;
	return this;
}

gui::button* gui::buttonbuilder::build()
{
	return new button(this);
}

gui::button* gui::create_text_button(int _x, int _y, const char* text, const char* font_file, int _size, int r, int g, int b)
{
	gui::buttonbuilder _builder;
	_builder.set_x(_x)
		->set_y(_y)
		->text(text, font_file, _size)
		->color(r, g, b);
	return _builder.build();
}
