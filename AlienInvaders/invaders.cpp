#include "invaders.h"
scoreboard* _scoreboard;

//TODO need to move constants into a file
void start_screen() {
	
	start_screen_running = true;
	gui::button* start_button = gui::create_text_button(450, 700, "Start Game", "../resources/fonts/pirulen.ttf", 12, 255, 255, 255);
	
	start_button->add_listener(null_function, gui::mouse_event_type::MOUSE_DOWN);
	start_button->add_listener(start_button_function_up, gui::mouse_event_type::MOUSE_UP);

	staticdisplaybuilder _staticdisplybuilder;
	_staticdisplybuilder.pos_x(SCREEN_WIDTH/4)->pos_y(SCREEN_HEIGHT/4);
	//TODO need to put this file in XML
	_staticdisplybuilder.image("../resources/images/titlescreen.png");

	staticdisplayobject* _background = _staticdisplybuilder.build_image();


	ALLEGRO_TIMER* timer = get_timer();
	ALLEGRO_EVENT_QUEUE* a_event_q = al_create_event_queue();
	ALLEGRO_EVENT event;
	
	al_register_event_source(a_event_q, al_get_display_event_source(display));
	al_register_event_source(a_event_q, al_get_timer_event_source(timer));
	al_register_event_source(a_event_q, al_get_mouse_event_source());
	al_start_timer(timer);
	
	while (start_screen_running) {
		al_wait_for_event(a_event_q, &event);
		//gui::mouse_event _mouse_event;
		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			start_button->draw();
			_background->draw();
			al_flip_display();
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		{
			gui::mouse_event mouse_event(event.mouse.x, event.mouse.y, gui::mouse_event_type::MOUSE_UP);
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			gui::mouse_event mouse_event(event.mouse.x, event.mouse.y, gui::mouse_event_type::MOUSE_DOWN);
			break;
		}
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));
		
		if(al_is_event_queue_empty(a_event_q)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));	
		}

	}
	//al_destroy_timer(timer);
	al_destroy_event_queue(a_event_q);
	delete start_button;
	delete _background;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_stop_timer(timer);
}


void difficulty_screen() {
	difficulty_screen_running = true;
	gui::button* easy_button = gui::create_text_button(150, 500, "Easy", "../resources/fonts/pirulen.ttf", 12, 255, 255, 255);

	easy_button->add_listener(null_function, gui::mouse_event_type::MOUSE_DOWN);
	easy_button->add_listener(easy_button_fn, gui::mouse_event_type::MOUSE_UP);

	gui::button* hard_button = gui::create_text_button(450, 500, "Hard", "../resources/fonts/pirulen.ttf", 12, 255, 255, 255);

	hard_button->add_listener(null_function, gui::mouse_event_type::MOUSE_DOWN);
	hard_button->add_listener(hard_button_fn, gui::mouse_event_type::MOUSE_UP);

	gui::button* hardcore_button = gui::create_text_button(750, 500, "Hardcore", "../resources/fonts/pirulen.ttf", 12, 255, 255, 255);

	hardcore_button->add_listener(null_function, gui::mouse_event_type::MOUSE_DOWN);
	hardcore_button->add_listener(hardcore_button_fn, gui::mouse_event_type::MOUSE_UP);


	ALLEGRO_TIMER* timer = get_timer();
	ALLEGRO_EVENT_QUEUE* a_event_q = al_create_event_queue();
	ALLEGRO_EVENT event;

	al_register_event_source(a_event_q, al_get_display_event_source(display));
	al_register_event_source(a_event_q, al_get_timer_event_source(timer));
	al_register_event_source(a_event_q, al_get_mouse_event_source());
	al_start_timer(timer);

	while (difficulty_screen_running) {
		al_wait_for_event(a_event_q, &event);
		//gui::mouse_event _mouse_event;
		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			easy_button->draw();
			hard_button->draw();
			hardcore_button->draw();
			al_flip_display();
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		{
			gui::mouse_event mouse_event(event.mouse.x, event.mouse.y, gui::mouse_event_type::MOUSE_UP);
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			gui::mouse_event mouse_event(event.mouse.x, event.mouse.y, gui::mouse_event_type::MOUSE_DOWN);
			break;
		}
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (al_is_event_queue_empty(a_event_q)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_event_queue(a_event_q);
	delete easy_button;
	delete hardcore_button;
	delete hard_button;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_stop_timer(timer);
}
std::string get_string( const char* _array, int size) {
	std::stringstream _ss;
	for (int i = 0; i < size; i++) {
		_ss << _array[i];
	}
	return _ss.str();
}

void prompt() {
	running = true;
	ALLEGRO_FONT* font = al_load_ttf_font("../resources/fonts/pirulen.ttf", 16, 0);
	gui::button* done_button = gui::create_text_button(750, 750, "Done", "../resources/fonts/pirulen.ttf", 12, 255, 255, 255);
	done_button->add_listener(null_function, gui::mouse_event_type::MOUSE_DOWN);
	done_button->add_listener(done_function, gui::mouse_event_type::MOUSE_UP);

	ALLEGRO_TIMER* timer = get_timer();
	ALLEGRO_EVENT_QUEUE* a_event_q = al_create_event_queue();
	ALLEGRO_EVENT event;

	al_register_event_source(a_event_q, al_get_display_event_source(display));
	al_register_event_source(a_event_q, al_get_timer_event_source(timer));
	al_register_event_source(a_event_q, al_get_mouse_event_source());
	al_register_event_source(a_event_q, al_get_keyboard_event_source());
	al_start_timer(timer);

	char name[ALLEGRO_KEY_MAX];
	memset(name, 0, sizeof(name));
	int i = 0;
	while (running) {
		al_wait_for_event(a_event_q, &event);
		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			done_button->draw();
			al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, "Please enter your name: ");
			al_draw_text(font, al_map_rgb(255, 255, 255), 100, 100, 0, name);
			al_flip_display();
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		{
			gui::mouse_event mouse_event(event.mouse.x, event.mouse.y, gui::mouse_event_type::MOUSE_UP);
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			gui::mouse_event mouse_event(event.mouse.x, event.mouse.y, gui::mouse_event_type::MOUSE_DOWN);
			break;
		}
		case ALLEGRO_EVENT_KEY_CHAR: {
			name[i++] = event.keyboard.unichar;
			break;
		}
			
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (al_is_event_queue_empty(a_event_q)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}
	
	_scoreboard = new scoreboard("../resources/gamedata/highscores/highscores.txt");
	_scoreboard->add(get_string(name, i), get_score());
	_scoreboard->sort();
	_scoreboard->trim();
	_scoreboard->save();
	al_destroy_event_queue(a_event_q);
	delete done_button;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_stop_timer(timer);
	al_destroy_font(font);

}
void show_scores() {
	running = true;
	gui::button* done_button = gui::create_text_button(750, 750, "Done", "../resources/fonts/pirulen.ttf", 12, 255, 255, 255);
	done_button->add_listener(null_function, gui::mouse_event_type::MOUSE_DOWN);
	done_button->add_listener(done_function, gui::mouse_event_type::MOUSE_UP);

	gui::button* replay_button = gui::create_text_button(150, 750, "Exit", "../resources/fonts/pirulen.ttf", 12, 255, 255, 255);
	replay_button->add_listener(null_function, gui::mouse_event_type::MOUSE_DOWN);
	replay_button->add_listener(overall_done_func, gui::mouse_event_type::MOUSE_UP);


	ALLEGRO_TIMER* timer = get_timer();
	ALLEGRO_EVENT_QUEUE* a_event_q = al_create_event_queue();
	ALLEGRO_EVENT event;
	ALLEGRO_FONT* font = al_load_ttf_font("../resources/fonts/pirulen.ttf", 12, 0);

	al_register_event_source(a_event_q, al_get_display_event_source(display));
	al_register_event_source(a_event_q, al_get_timer_event_source(timer));
	al_register_event_source(a_event_q, al_get_mouse_event_source());
	al_register_event_source(a_event_q, al_get_keyboard_event_source());
	al_start_timer(timer);
	
	int i;
	std::vector<score> scores = _scoreboard->get_scores();

	while (running) {
		al_wait_for_event(a_event_q, &event);
		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			done_button->draw();
			replay_button->draw();
			for (i = 0; i < 10; i++) {
				score _score = scores[i];
				al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, (75 + (50*i)), 0, _score.to_string().c_str());
			}
			al_flip_display();
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		{
			gui::mouse_event mouse_event(event.mouse.x, event.mouse.y, gui::mouse_event_type::MOUSE_UP);
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			gui::mouse_event mouse_event(event.mouse.x, event.mouse.y, gui::mouse_event_type::MOUSE_DOWN);
			break;
		}
		case ALLEGRO_EVENT_KEY_CHAR: {
			
		}

		}
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (al_is_event_queue_empty(a_event_q)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

	al_destroy_event_queue(a_event_q);
	delete done_button;
	delete replay_button;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_stop_timer(timer);
	al_destroy_font(font);

}

int main()
{
	init_allegro();
	display = get_display();

	game_is_running = true;
	while (game_is_running) {
		start_screen();
		difficulty_screen();
		play_game(_difficulty);
		prompt();
		//TODO fix the replay button
		show_scores();
	}
	
	shut_down_allegro();
	return 0;
}