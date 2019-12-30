#include "GameManager.h"

//#include "functions.cpp"
//TODO
//abstract out the constants like files they will go in constants and be set by GM -- 
	//using XML need function and need to remove the constants
//fix shooting of enermies
//fix sorting layerphysics for enemies
//do we need player controller?
//add main menu
//add buttons observer and state of buttons
//add difficulty must be abstracted out
//include state of game high score saving and maybe boss fights
//introduce special weapon functionality
//add health bar
game_constants _constants = game_constants::load(DEFAULT_GAME_SETTINGS_LOCATION);
healthbar_serializer _health_bar = healthbar_serializer::load(DEFAULT_HEALTH_BAR_SETTINGS_LOCATION);
ALLEGRO_EVENT_QUEUE* a_event_q = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_DISPLAY* disp = NULL;
ship* spaceship = NULL;
background* _background = NULL;
ALLEGRO_THREAD* blast_thread = NULL;
ALLEGRO_THREAD* cleanup_thread = NULL;
ALLEGRO_THREAD* stars_thread = NULL;
controller* _enemycontroller = new enemycontroller();
colliderbodybuilder enemy_blast_builder;
colliderbodybuilder _colliderbodybuilder;
//queue<explosion*, 5>* ex_queue = new queue<explosion*, 5>();

std::vector<gameobject*> blasts;
std::vector<gameobject*> enemies;
std::vector<gameobject*> enemy_blasts;
ALLEGRO_FONT* font;
healthbar* _healthbar;

struct explosion_drawer;
static std::vector<staticdisplayobject*>* explosions;
static physicsengine* _physicsengine = new physicsengine();
static std::vector<gameobject*>* _points = new std::vector<gameobject*>();
//TODO need to add a sorting layer
//TODO need to add scenes ass levels

long score = 0;

static void* calculate_blasts(ALLEGRO_THREAD* thr, void* arg);
static void* cleanup(ALLEGRO_THREAD* thr, void* arg);

void* stars(ALLEGRO_THREAD* thread, void* arg);

bool compare_to_top(void* arg1) {
	gameobject* _gameobject = (gameobject*)arg1;
	if (0.0f > _gameobject->get_y_position()) {
		return true;
	}
	
	return false;
}

bool compare_to_bottom(void* arg1) {
	gameobject* _gameobject = (gameobject*)arg1;
	if (SCREEN_HEIGHT < _gameobject->get_y_position()) {
		return true;
	}
	return false;
}


void must_init(bool test, const char* description)
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}

void init_game()
{
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");
	must_init(al_init_image_addon(), "image addon");
	must_init(al_install_mouse(), "mouse");
	must_init(al_init_font_addon(), "font");
	must_init(al_init_ttf_addon(), "ttf");

	timer = al_create_timer(1.0 / 30.0);

	must_init(timer, "timer");

	a_event_q = al_create_event_queue();
	must_init(a_event_q, "queue");

	font = al_load_ttf_font("../resources/fonts/pirulen.ttf", 12, 0);

	must_init(font, "font");

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

	disp = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	must_init(disp, "display");
	al_hide_mouse_cursor(disp);



	must_init(al_init_primitives_addon(), "primitives");

	al_register_event_source(a_event_q, al_get_keyboard_event_source());
	al_register_event_source(a_event_q, al_get_display_event_source(disp));
	al_register_event_source(a_event_q, al_get_timer_event_source(timer));
	al_register_event_source(a_event_q, al_get_mouse_event_source());


	enemy_blast_builder.set_damage(ENEMY_DAMAGE)
		->set_image(_constants._enemy._blast._file.c_str())
		->set_on_end(_constants._enemy._blast._explosion.c_str())
		->sizex(DEFAULT_BLAST_SIZE)
		->sizey(DEFAULT_BLAST_SIZE)
		->sorting_layer(1);

	spritebuilder* objectbuilder = new spritebuilder();
	objectbuilder->
		pos_x(100.0)->
		pos_y(100.0)->
		sizex(DEFAULT_SIZE)->
		sizey(DEFAULT_SIZE)->
		sorting_layer(1);
	

		_colliderbodybuilder.set_damage(PLAYER_DAMAGE)
		->set_image(_constants._player._blast._file.c_str())
		->set_on_end(_constants._player._blast._explosion.c_str())
		->sizex(DEFAULT_BLAST_SIZE)
		->sizey(DEFAULT_BLAST_SIZE)
		->sorting_layer(1);
	
		spritebuilder* shipbuilder = (spritebuilder*)objectbuilder;

		shipbuilder->set_health(PLAYER_HEALTH)
			->set_animation(_constants._player._animations)
			->set_damage(PLAYER_DAMAGE)
			->set_utility(&_colliderbodybuilder)
			->set_on_end(_constants._player._explosion.c_str());

	spaceship = (ship*)shipbuilder->build_player();
	delete shipbuilder;

	staticdisplaybuilder* _staticdisplybuilder = new staticdisplaybuilder();
	_staticdisplybuilder->pos_x(600.0)->pos_y(100.0);
	//TODO need to put this file in XML
	_staticdisplybuilder->image("../resources/images/level1.png");

	_background = (background*)_staticdisplybuilder->build_background();

	explosions = new std::vector<staticdisplayobject*>();
	//blast_thread = al_create_thread(calculate_blasts, NULL);
	
	//cleanup_thread = al_create_thread(cleanup, _synchronizer);

	//TODO for test
	//explosions = new std::vector<explosion*>();
	//if (pthread_create(&t0, NULL, create_new_asteroid, NULL) == -1) {
	//	puts("cant create thread");
	//}
	staticdisplaybuilder _healthbarbuilder;
	_healthbarbuilder.pos_x(10)->pos_y(0)->sorting_layer(1);
	_healthbarbuilder.set_animation(_health_bar._animations);
	_healthbar = (healthbar*) _healthbarbuilder.build_healthbar();
}

//TODO need to close resources
	//on close close resources and free memory

void destroy(void* arg, bool hasBeenAllocated) {
	std::vector<gameobject*>* _gameobjects = (std::vector<gameobject*>*) arg;
	while (!_gameobjects->empty()) {
		delete _gameobjects->back(), _gameobjects->pop_back();
	}
	if (hasBeenAllocated)
		delete _gameobjects;

}
void destroy()
{
	try {
		destroy(explosions, true);
		destroy(&blasts, false);
		destroy(&enemies, false);
		destroy(_points, true);
		destroy(&enemy_blasts, false);

		al_destroy_thread(stars_thread);
		//al_destroy_thread(cleanup_thread);
		delete spaceship;
		al_destroy_event_queue(a_event_q);
		al_destroy_timer(timer);
		al_destroy_display(disp);
		al_destroy_font(font);
		delete _background;
		al_shutdown_primitives_addon();
		al_shutdown_image_addon();
		al_shutdown_font_addon();
		al_shutdown_ttf_addon();
		delete _physicsengine;
		delete _enemycontroller;
	}
	catch (std::exception e) {
		OutputDebugString(e.what());
	}
	
}

void cleanup_resource(void* arg, bool compare_boundary(void*)) {
	try {
		std::vector<gameobject*>* resource = (std::vector<gameobject*>*)arg;
		for (int i = resource->size() - 1; i >= 0; i--) {
			gameobject* _gameobject = (*resource)[i];
			if (compare_boundary(_gameobject)) {
				resource->erase(resource->begin() + i);
				delete _gameobject;
			}
		}
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}
}

void cleanup_resources() {
	try {
	
		//TODO is there a resouce leak if destructor is not called on subtype?
		cleanup_resource(&blasts, compare_to_top);
		cleanup_resource(&enemy_blasts, compare_to_bottom);
		cleanup_resource(&enemies, compare_to_bottom);
		
		int i;
		explosion* _explosion;
		for (i = explosions->size() - 1; i >= 0; i--) {
			_explosion = (explosion*)(*explosions)[i];
			if (_explosion->is_drawn()) {
				explosions->erase(explosions->begin() + i);
				delete _explosion;
			}

		}
	}

	catch (std::exception e) {
		throw std::exception("Failed to erase resource");
	}

	
}

void draw(void* arg) {
	try {
		std::vector<gameobject*>* _gameobjects = (std::vector<gameobject*>*) arg;
		for (int i = 0; i < _gameobjects->size(); i++) {
			(*_gameobjects)[i]->draw();
		}

	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}



}



void draw_all() {
	try {
		//TODO add sorting to this function call

		_background->draw();
		spaceship->draw();
		draw(&blasts);
		draw(explosions);
		draw(&enemies);
		draw(&enemy_blasts);
		_healthbar->draw(spaceship->get_health());
		int i;
		ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
		for (i = 0; i < _points->size(); i++) {
			//FIX this should just be calling ->draw();
			al_draw_pixel((*_points)[i]->get_x_position(), (*_points)[i]->get_y_position(), color);
		}
		
		
		al_draw_text(font, al_map_rgb(255, 255, 255),9*SCREEN_WIDTH/10, 0, 0, format_string(score, '0', 8).c_str());

	}
	catch (std::exception e) {
		std::stringstream _ss;
		_ss << "Failed to draw: " << e.what();
		throw std::exception(_ss.str().c_str());
	}
}

void calculate_collisions() {
	try {
		int number_of_collisions = _physicsengine->evaluate_collisions(&enemies, &blasts, explosions);
		score = score + number_of_collisions * 5;
	}
	catch (std::exception& e) {
		std::stringstream _ss;
		_ss << "Failed to evaluate the collisions: " << e.what();
		throw std::exception(_ss.str().c_str());
	}
	

}
//TODO clean up resources
void spawn_enemies() {
	int random_number = rand() % 50;
	std::vector<std::string> animations = _constants._enemy._animations;
	const char* blast_file = _constants._enemy._blast._file.c_str();
	if (random_number == 1) {
		int x = rand() % SCREEN_WIDTH;
		spritebuilder _enemybuilder;
		_enemybuilder.sizex(DEFAULT_SIZE)->sizey(DEFAULT_SIZE)->sorting_layer(1);
		_enemybuilder.set_health(ENEMY_HEALTH)
			->set_animation(_constants._enemy._animations)
			->set_damage(ENEMY_DAMAGE)
			->set_on_end(_constants._enemy._explosion.c_str())
			->set_utility(&enemy_blast_builder);
		_enemybuilder.pos_x(x)->pos_y(-10);
		enemy* _enemy = (enemy*)_enemybuilder.build_computer();

		if (!_enemy)
			throw std::exception("Failed to generate a new enemy");
		enemies.push_back(_enemy);
	}
}

void update_all_enemies() {
	
	try {
		//TODO use parameter speed to move sprite
		for (int i = 0; i < enemies.size(); i++) {
			_enemycontroller->move_sprite(enemies[i], ENEMY_SPEED, NULL);
			_enemycontroller->fire(enemies[i], &enemy_blasts);
		}
	}
	catch (std::exception e) {
		throw std::exception("Failed to update enemy");
	}
	
}


void update()
{
	try {

		for (int i = 0; i < blasts.size(); i++) {
			blasts[i]->increment_y_pos(BLAST_SPEED);
		}
	}
	catch (std::exception e) {
		std::stringstream _ss;
		_ss << "Cannot increment blast: " << e.what();
		OutputDebugString(_ss.str().c_str());
	}
	
	try {
		for (int i = 0; i < enemy_blasts.size(); i++) {
			enemy_blasts[i]->increment_y_pos(ENEMY_BLAST_SPEED);
		}
	}catch (std::exception e) {
		std::stringstream _ss;
		_ss << "Cannot increment blast: " << e.what();
		OutputDebugString(_ss.str().c_str());
	}
	try {
		cleanup_resources();
		calculate_collisions();
		draw_all();
		spawn_enemies();
		update_all_enemies();
	}
	catch (std::exception e) {
		OutputDebugString(e.what());
	}
	

	al_flip_display();

	
}


void handle_event_mouse_click(ALLEGRO_EVENT* event) {
	std::vector<twodcolliderbody*> blasts_from_fire;
	if ((*event).mouse.button == 1) {
		blasts_from_fire = spaceship->fire();
		
		if (!(&blasts_from_fire))
			throw std::exception("Failed to create blasts");

		for (twodcolliderbody* blast_ : blasts_from_fire) {
			blasts.push_back((blast*)blast_);
		}
		
	}
}

//TODO should we use controller?
void handle_mouse_movement(ALLEGRO_EVENT* event) {
	try {
		int new_x_pos = (*event).mouse.x;
		int new_y_pos = (*event).mouse.y;

		int old_x_pos = spaceship->get_x_position();
		int old_y_pos = spaceship->get_y_position();
		spaceship->set_position(new_x_pos, new_y_pos);
		bool same_layer = false;
		_physicsengine->evaluate_sorting(spaceship, &enemies, &same_layer);

		if (same_layer) {
			spaceship->set_position(old_x_pos, old_y_pos);
			return;
		}

		spaceship->set_position(spaceship->get_x_position(), spaceship->get_y_position() - 50.0);
	}
	catch (std::exception e) {
		OutputDebugString(e.what());
	}
	
	
}

//Need to take this out of gamemanger and put into game
int main()
{

	init_game();

	//al_register_event_source(event_queue, &data1.event_source);
	bool stars_ready = false;

	stars_thread = al_create_thread(stars, &stars_ready);
	al_start_thread(stars_thread);

	while (!stars_ready) {
		//al_wait_cond(stars_cond, NULL);
	}
	//al_start_thread(cleanup_thread);

	bool done = false;
	bool redraw = true;


	al_start_timer(timer);

	bool isRunning = true;
	double old_time = al_get_time();


	//TODO create a controller
	//TODO maybe better to switch to switch loop
	ALLEGRO_EVENT event;

	while (isRunning) {

		al_wait_for_event(a_event_q, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// game logic goes here.
			update();
			redraw = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			isRunning = false;
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			handle_mouse_movement(&event);
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			handle_event_mouse_click(&event);
			break;
		}

		if (redraw && al_is_event_queue_empty(a_event_q)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			
		}
	}
	//TODO this will have to be changed once we remove this hard loop		
		//need user input to get name
	
	scoreboard _scoreboard("../resources/gamedata/highscores/highscores.txt");
	_scoreboard.add("jason", score);
	_scoreboard.sort();
	_scoreboard.trim();
	_scoreboard.save();

	destroy();

	//void* result;
	//if (pthread_join(t0, &result) == -1) {
	//	puts("error joining");
	//}

	return 0;
}

void* stars(ALLEGRO_THREAD* thread, void* arg) {
	int i;
	bool* is_ready = (bool*)arg;

	for (i = 0; i < 50; i++) {
		_points->push_back(staticdisplayfactory::create_point(rand() % SCREEN_HEIGHT, rand() % SCREEN_WIDTH));
	}
	
	*is_ready = true;
	float rate = 10.0;
	float y_position;
	while (!al_get_thread_should_stop(thread)) {

		must_init(al_init_primitives_addon(), "primitives");
		int x, y;

		for (i = 0; i < _points->size(); i++) {
			y_position = (*_points)[i]->get_y_position();
			if(y_position > SCREEN_HEIGHT)
				(*_points)[i]->set_y_position(0);
			
			(*_points)[i]->increment_y_pos(rate);
		}
		al_rest(0.04);

	}

	return NULL;

}
