#pragma once
#include <vector>
#include "boxcollider.h"
#include <map>
#include <allegro5\bitmap.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_font.h>
namespace gui {
	class button_listener;
	enum class mouse_event_type;
	class buttonbuilder;
	class mouse_event;
	//TODO may need a superclass for button?
	//need to use some kind of reflection to when type is added
	class button {
	private:
		mouse_event_type _buttonstate;
		std::map<mouse_event_type ,button_listener*> _listeners;
		boxcollider* _boxcollider;
		ALLEGRO_BITMAP* _bitmap;
		ALLEGRO_FONT* _font;
		const char* _text;
		int _x, _y, _size_x, _size_y;
		ALLEGRO_COLOR _color;
	protected:
		void update(mouse_event_type, mouse_event*);
		boxcollider* get_collider();
		void notify();
	public:
		friend class button_listener;
		friend class buttonbuilder;
		friend class mouse_event;
		button();
		button(buttonbuilder*);
		~button();
		void add_listener(void* action(void*, void*), mouse_event_type);
		void draw();
		//void draw_text();
		
	};

	class button_listener {
		typedef void* (*action_function)(void*, void*);
	private:
		button* _button;
		action_function _action;
	protected:
		void _event_(mouse_event*, mouse_event_type);
	public:
		
		friend class mouse_event;
		friend class button;
		button_listener(button*, void* action(void*, void*));
		button_listener();
		virtual ~button_listener();
		
	};

	/*class mouse_down_listener : public button_listener {
	public:
		mouse_down_listener(button*, void* action(void*, void*));
		mouse_down_listener();
		virtual ~mouse_down_listener();
	};

	class mouse_up_listener : public button_listener{
	public:
		mouse_up_listener(button*, void* action(void*, void*));
		mouse_up_listener();
		virtual ~mouse_up_listener();
	};*/

	enum class mouse_event_type {
		MOUSE_DOWN,
		MOUSE_UP,
		NONE
	};
	
	class buttonbuilder {
	private:
		float _x, _y, _size_x, _size_y;
		ALLEGRO_BITMAP* _bitmap;
		ALLEGRO_FONT* _font;
		const char* _text;
		ALLEGRO_COLOR _color;
	public:
		friend class button;
		buttonbuilder();
		~buttonbuilder();
		buttonbuilder* image(const char*);
		buttonbuilder* text(const char*, const char*, int);
		buttonbuilder* color(int, int, int);
		buttonbuilder* set_x(int);
		buttonbuilder* set_y(int);
		buttonbuilder* size_x(int);
		buttonbuilder* size_y(int);
		button* build();
	};

	class mouse_event {
	private:
		//TODO replace with linked hashmap
	//	static std::map<mouse_event_type, std::vector<button_listener*>>* _listeners;
		static std::vector<button*>* _buttons;
	public:
		mouse_event(int, int, mouse_event_type);
		~mouse_event();
		static void register_(button*);
		static void unregister_(button*);
		static void delete_resources();
	};
	gui::button* create_text_button(int, int, const char*, const char*, int, int, int, int);
	//std::map<mouse_event_type, std::vector<button_listener*>>* mouse_event::_listeners = new std::map<mouse_event_type, std::vector<button_listener*>>();
};

