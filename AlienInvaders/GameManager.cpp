#include "GameManager.h"

//#include "functions.cpp"
//TODO
//abstract out the constants like files they will go in constants and be set by GM -- 
	//using XML need function and need to remove the constants
//fix sorting layerphysics for enemies
//do we need player controller?
//add main menu
//add buttons observer and state of buttons
//add difficulty must be abstracted out
//include state of game high score saving and maybe boss fights
//introduce special weapon functionality
//add health bar
//cleanup gamemanager by using a script and running script with two functions update and start
//TODO need to fix memory problem
//TODO cleanup gamemanager
//add gui elements like buttons see above ideas
//need to have game using gamemanger and have 3 pages start menu/difficulty menu/ and game
//TODO add a way to get hearts
//STILL need sounds
//left TODO
//cleanup gamemanager and put things in constant files
//change difficulty settings
//TODO cleanup game manager
game_constants _constants = game_constants::load(DEFAULT_GAME_SETTINGS_LOCATION);
healthbar_serializer _health_bar = healthbar_serializer::load(DEFAULT_HEALTH_BAR_SETTINGS_LOCATION);
ALLEGRO_EVENT_QUEUE* a_event_q = NULL;
ALLEGRO_TIMER* timer = NULL;
ship* spaceship = NULL;
staticdisplayobject* _background = NULL;
ALLEGRO_THREAD* blast_thread = NULL;
ALLEGRO_THREAD* cleanup_thread = NULL;
ALLEGRO_THREAD* stars_thread = NULL;
controller* _enemycontroller = new enemycontroller();
colliderbodybuilder enemy_blast_builder;
colliderbodybuilder _colliderbodybuilder;
colliderbodybuilder _specialbodybuilder;
colliderbodybuilder _heartbuilder;
int time_of_last_special;
int is_ready;
//queue<explosion*, 5>* ex_queue = new queue<explosion*, 5>();
staticdisplayobject* ready_image;
std::vector<gameobject*> blasts;
std::vector<gameobject*> enemies;
std::vector<gameobject*> enemy_blasts;
ALLEGRO_FONT* font;
healthbar* _healthbar;
int _difficulty;
ALLEGRO_DISPLAY* disp = NULL;
struct explosion_drawer;
static std::vector<gameobject*> explosions;
static std::vector<gameobject*> _hearts;
static physicsengine* _physicsengine = new physicsengine();
static std::vector<gameobject*> _points;
//TODO need to add a sorting layer
//TODO need to add scenes ass levels
bool is_running;
long _score = 0;
static int game_sequence = 0;
void* stars(ALLEGRO_THREAD* thread, void* arg);


std::string format_string(int score, char pad_with, int number_to_pad_to) {
	std::ostringstream out;
	out << std::internal << std::setfill(pad_with) << std::setw(number_to_pad_to) << score;
	return out.str();
}

void set_difficulty(difficulty _d) {
	_difficulty = static_cast<int>(_d);
}

//TODO need to move pointer functions to seperate files
bool compare_to_top(void* arg1) {
	gameobject* _gameobject = (gameobject*)arg1;
	if (-250.0f > _gameobject->get_y_position()) {
		return true;
	}
	
	return false;
}

bool compare_to_bottom(void* arg1) {
	gameobject* _gameobject = (gameobject*)arg1;
	if (SCREEN_HEIGHT + 250.0f < _gameobject->get_y_position()) {
		return true;
	}
	return false;
}

void* bounce_enemy(void* arg1, void* arg2) {
	enemy* _enemyA = (enemy*)arg1;
	enemy* _enemyB = (enemy*)arg2;
	_enemyA->reverse_x_rate();
	_enemyB->reverse_x_rate();
	return nullptr;
}

void* collide(void* arg1, void* arg2) {
	sprite* _sprite = (sprite*)arg1;
	blast* _collider = (blast*)arg2;
	int score_to_increase = 0;
	int dmg = _collider->get_damage();

	if (!_sprite->take_damage(dmg)) {
		explosions.push_back(_sprite->explode());
		score_to_increase += 10;
	}

	if (!_collider->is_invulerable()) {
		explosions.push_back(_collider->explode());
		delete _collider;
	}

	score_to_increase++;
	_score = _score + score_to_increase * 5;
	return NULL;
}

void* heal(void* arg1, void* arg2) {
	sprite* _sprite = (sprite*)arg1;
	heart* _collider = (heart*)arg2;
	_sprite->heal(_collider->get_healing_power());
	delete _collider;
	return NULL;
}

void* test_ptr_function(void* arg1, void* arg2) {
	gui::mouse_event* _event = (gui::mouse_event*) arg1;
	gui::mouse_event_type* _type = (gui::mouse_event_type*) arg2;
	std::cout << "Button clicked" << std::endl;
	return NULL;
}

void must_init(bool test, const char* description)
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}

void init_allegro() {
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");
	must_init(al_init_image_addon(), "image addon");
	must_init(al_install_mouse(), "mouse");
	must_init(al_init_font_addon(), "font");
	must_init(al_init_ttf_addon(), "ttf");
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	must_init(al_init_primitives_addon(), "primitives");
	disp = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	must_init(disp, "display");
	timer = al_create_timer(1.0 / 30.0);
	must_init(timer, "timer");
}

ALLEGRO_DISPLAY* get_display()
{
	return disp;
}

ALLEGRO_TIMER* get_timer()
{
	return timer;
}



void init_game()
{
	is_ready = 0;
	

	font = al_load_ttf_font("../resources/fonts/pirulen.ttf", 12, 0);

	must_init(font, "font");

	enemy_blast_builder.set_utility(ENEMY_DAMAGE)
		->set_image(_constants._enemy._blast._file.c_str())
		->set_on_end(_constants._enemy._blast._explosion.c_str())
		->invulnerability(false)
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
	

		_colliderbodybuilder.set_utility(PLAYER_DAMAGE)
			->set_image(_constants._player._blast._file.c_str())
			->set_on_end(_constants._player._blast._explosion.c_str())
			->invulnerability(false)
			->sizex(DEFAULT_BLAST_SIZE)
			->sizey(DEFAULT_BLAST_SIZE)
			->sorting_layer(1);
	
		_specialbodybuilder.set_utility(SPECIAL_DAMAGE)
			->set_image(_constants._player._special.c_str())
			->invulnerability(true)
			->sizex(SPECIAL_BLAST_SIZE_X)
			->sizey(SPECIAL_BLAST_SIZE_Y)
			->sorting_layer(1);

		_heartbuilder.set_utility(HEART_HEALING_POWER)
			->set_image(_constants._heart.c_str())
			->invulnerability(false)
			->sizex(HEART_SIZE)
			->sizey(HEART_SIZE)
			->sorting_layer(2)
			->pos_y(-10);

		spritebuilder* shipbuilder = (spritebuilder*)objectbuilder;

		shipbuilder->set_health(PLAYER_HEALTH)
			->set_animation(_constants._player._animations)
			->set_damage(PLAYER_DAMAGE)
			->add_utility(&_colliderbodybuilder)
			->add_utility(&_specialbodybuilder)
			->set_on_end(_constants._player._explosion.c_str());

	spaceship = (ship*)shipbuilder->build_player();
	delete shipbuilder;

	staticdisplaybuilder _staticdisplybuilder;
	_staticdisplybuilder.pos_x(600.0)->pos_y(100.0);
	_staticdisplybuilder.image("../resources/images/level1.png");

	_background = (staticdisplayobject*)_staticdisplybuilder.build_image();
	staticdisplaybuilder _healthbarbuilder;
	_healthbarbuilder.pos_x(10)->pos_y(-30)->sorting_layer(1);
	_healthbarbuilder.set_animation(_health_bar._animations);
	_healthbar = (healthbar*) _healthbarbuilder.build_healthbar();

	staticdisplaybuilder _staticbuilder;
	_staticbuilder.pos_x(110)->pos_y(-10)->sorting_layer(1);
	_staticbuilder.set_animation(_constants._notifications);
	ready_image = _staticbuilder.build_image();
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
		destroy(&explosions, false);
		destroy(&blasts, false);
		destroy(&enemies, false);
		destroy(&_points, true);
		destroy(&enemy_blasts, false);
		delete spaceship;
		al_destroy_event_queue(a_event_q);		
		al_destroy_font(font);
		delete _background;		
		delete _physicsengine;
		delete _enemycontroller;
		delete ready_image;
		delete _healthbar;
		//TODO need to clean up resources
	}
	catch (std::exception e) {
		OutputDebugString(e.what());
	}
	
}
void clear_score()
{
	_score = 0;
}
void shut_down_allegro() {
	try {
		al_shutdown_primitives_addon();
		al_shutdown_image_addon();
		al_shutdown_font_addon();
		al_shutdown_ttf_addon();
		al_destroy_timer(timer);
		al_destroy_display(disp);
		al_uninstall_mouse();
		al_uninstall_keyboard();
	}
	catch (std::exception e) {
		OutputDebugString(e.what());
	}
	
}

int get_score()
{
	return _score;
}

//TODO it might not clean up vector
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
		cleanup_resource(&_hearts, compare_to_bottom);
		
		int i;
		explosion* _explosion;
		for (i = explosions.size() - 1; i >= 0; i--) {
			_explosion = (explosion*)explosions[i];
			if (_explosion->is_drawn()) {
				explosions.erase(explosions.begin() + i);
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
		draw(&explosions);
		draw(&enemies);
		_healthbar->draw(spaceship->get_health());
		int i;
		ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
		for (i = 0; i < _points.size(); i++) {
			//FIX this should just be calling ->draw();
			al_draw_pixel(_points[i]->get_x_position(), _points[i]->get_y_position(), color);
		}
		
		
		al_draw_text(font, al_map_rgb(255, 255, 255),9*SCREEN_WIDTH/10, 0, 0, format_string(_score, '0', 8).c_str());
		ready_image->draw(is_ready);
		//_test_button->draw();
	}
	catch (std::exception e) {
		std::stringstream _ss;
		_ss << "Failed to draw: " << e.what();
		throw std::exception(_ss.str().c_str());
	}
}

void calculate_collisions() {
	try {
		int number_of_collisions;
		int i;
		sprite* _sprite;
		
		for (i = enemies.size() - 1; i >= 0; i--) {
			_sprite = (sprite*)enemies[i];
			number_of_collisions = _physicsengine->evaluate_collisions(_sprite, &blasts, NULL, collide);
			if (_sprite->get_state() == spritestate::DEAD) {
				enemies.erase(enemies.begin() + i);
				delete _sprite;
			}
			
		}
		_physicsengine->evaluate_collisions(spaceship, &_hearts, NULL, heal);
		//int number_of_collisions = _physicsengine->evaluate_collisions(&enemies, &blasts, explosions);
		_physicsengine->evaluate_collisions(spaceship, &enemy_blasts, NULL, collide);
	}
	catch (std::exception& e) {
		std::stringstream _ss;
		_ss << "Failed to evaluate the collisions: " << e.what();
		throw std::exception(_ss.str().c_str());
	}


}
//TODO clean up resources
enemy* generate_enemy(int x) {
	spritebuilder _enemybuilder;
	_enemybuilder.sizex(DEFAULT_SIZE)->sizey(DEFAULT_SIZE)->sorting_layer(1);
	_enemybuilder.set_health(ENEMY_HEALTH)
		->set_animation(_constants._enemy._animations)
		->set_damage(ENEMY_DAMAGE)
		->set_on_end(_constants._enemy._explosion.c_str())
		->add_utility(&enemy_blast_builder);
	_enemybuilder.pos_x(x)->pos_y(-10);
	enemy* _enemy = (enemy*)_enemybuilder.build_computer();
	return _enemy;
}

void spawn_enemies() {
	int random_number = (rand() % (100 / _difficulty));
	//std::vector<std::string> animations = _constants._enemy._animations;
	//const char* blast_file = _constants._enemy._blast._file.c_str();
	if (random_number == 1) {
		int x = rand() % SCREEN_WIDTH;
		enemy* _enemy = generate_enemy(x);
		if (!_enemy)
			throw std::exception("Failed to generate a new enemy");

		bool same_layer = false;
		_physicsengine->evaluate_sorting(_enemy, &enemies, &same_layer, NULL);
		
		if (same_layer) {
			delete _enemy;
			return;
		}
		
		enemies.push_back(_enemy);
	}
}

void update_all_enemies() {
	int old_x, old_y;
	enemy* _enemy;
	bool same_layer;
	try {
		//TODO use parameter speed to move sprite
		for (int i = 0; i < enemies.size(); i++) {
			_enemy = (enemy*)enemies[i];
			old_x = _enemy->get_x_position();
			old_y = _enemy->get_y_position();
			
			_enemycontroller->move_sprite(_enemy, ENEMY_SPEED, NULL);
			same_layer = false;
			_physicsengine->evaluate_sorting(_enemy, &enemies, &same_layer, bounce_enemy);

			if (same_layer) {
				_enemy->set_position(old_x, old_y);
			
			}


			int random_chance = (rand() % 30) / _difficulty;
			if (random_chance == 1) {
				_enemycontroller->fire(_enemy, &enemy_blasts);
			}
		}
	}
	catch (std::exception e) {
		throw std::exception("Failed to update enemy");
	}

}

void spawn_hearts() {
	int random_number = rand() % 20;
	
	if (random_number == 1) {
		int x = rand() % SCREEN_WIDTH;
		_heartbuilder.pos_x(x);
		twodcolliderbody* _heart = _heartbuilder.build_heart();
		if (!_heart)
			throw std::exception("failed to create a heart");
		_hearts.push_back(_heart);
	}
}

void increment_y_and_draw(std::vector<gameobject*>* _gameobjects, float speed) {
	gameobject* _gameobject;
	for (int i = 0; i < _gameobjects->size(); i++) {
		_gameobject = (*_gameobjects)[i];
		_gameobject->increment_y_pos(speed);
		_gameobject->draw();
	}
}

void update()
{
	if (0 >= spaceship->get_health()) {
		is_running = false;
		return;
	}
		
	

	try {
		//TODO find a better way to change state
		if (is_ready == 1) {
			auto time = std::chrono::system_clock::now().time_since_epoch();
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(time);
			long _now = millis.count();
			if ((time_of_last_special + 10000) <= _now) {
				is_ready = 0;
			}
		}
		
		spawn_hearts();
		cleanup_resources();
		calculate_collisions();
		draw_all();
		spawn_enemies();
		update_all_enemies();

		try {
			increment_y_and_draw(&blasts, BLAST_SPEED);
			increment_y_and_draw(&enemy_blasts, ENEMY_BLAST_SPEED);
			increment_y_and_draw(&_hearts, HEART_SPEED);

		}
		catch (std::exception e) {
			std::stringstream _ss;
			_ss << "Cannot increment blast: " << e.what();
			OutputDebugString(_ss.str().c_str());
		}
	}
	catch (std::exception e) {
		OutputDebugString(e.what());
	}


	al_flip_display();


}


void handle_event_mouse_click(ALLEGRO_EVENT* event) {
//	gui::mouse_event _event((*event).mouse.x, (*event).mouse.y, gui::mouse_event_type::MOUSE_DOWN);
	if (event->mouse.button == 1) {
		std::vector<twodcolliderbody*> blasts_from_fire = spaceship->fire();

		if (!(&blasts_from_fire))
			throw std::exception("Failed to create blasts");

		for (twodcolliderbody* blast_ : blasts_from_fire) {
			blasts.push_back((blast*)blast_);
		}

	}
	else if (event->mouse.button == 2){
		if (is_ready == 0) {		
			twodcolliderbody* _blast = spaceship->fire2();
			if (!_blast)
				throw std::exception("Failed to create blasts");
			blasts.push_back(_blast);
			auto time = std::chrono::system_clock::now().time_since_epoch();
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(time);
			time_of_last_special = millis.count();
			is_ready = 1;
		}
		
	}
}

//TODO should we use controller?
void handle_mouse_movement(ALLEGRO_EVENT* event) {
	try {
		int new_x_pos = event->mouse.x;
		int new_y_pos = event->mouse.y;

		int old_x_pos = spaceship->get_x_position();
		int old_y_pos = spaceship->get_y_position();
		spaceship->set_position(new_x_pos, new_y_pos);
		bool same_layer = false;
		_physicsengine->evaluate_sorting(spaceship, &enemies, &same_layer, NULL);

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
void clear(std::vector<gameobject*>* _gameobjects ) {
	for (int i = _gameobjects->size() - 1; i >= 0; i--) {
		gameobject* _gameobject = (*_gameobjects)[i];
		_gameobjects->erase(_gameobjects->begin() + i);
		delete _gameobject;
		
	}
	
}


void clear_all() {
	clear(&enemies);
	clear(&enemy_blasts);
	clear(&blasts);
	clear(&_hearts);
	clear(&explosions);
	clear(&_points);

	spaceship->set_health(PLAYER_HEALTH);
	al_destroy_thread(stars_thread);
	al_destroy_event_queue(a_event_q);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
}

//Need to take this out of gamemanger and put into game
void run_game()
{
	
	//al_register_event_source(event_queue, &data1.event_source);
	bool stars_ready = false;
	a_event_q = al_create_event_queue();
	must_init(a_event_q, "queue");

	al_register_event_source(a_event_q, al_get_keyboard_event_source());
	al_register_event_source(a_event_q, al_get_display_event_source(disp));
	al_register_event_source(a_event_q, al_get_timer_event_source(timer));
	al_register_event_source(a_event_q, al_get_mouse_event_source());


	stars_thread = al_create_thread(stars, &stars_ready);
	al_start_thread(stars_thread);

	while (!stars_ready) {
		//al_wait_cond(stars_cond, NULL);
	}
	//al_start_thread(cleanup_thread);

	bool done = false;
	bool redraw = true;


	al_start_timer(timer);
	is_running = true;
	double old_time = al_get_time();
	spaceship->set_x_position(SCREEN_WIDTH / 2);
	spaceship->set_y_position(SCREEN_HEIGHT / 2);
	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	//TODO create a controller
	//TODO maybe better to switch to switch loop
	ALLEGRO_EVENT event;

	while (is_running) {

		al_wait_for_event(a_event_q, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// game logic goes here.
			update();
			redraw = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				is_running = false;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			is_running = false;
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
	al_stop_timer(timer);
	//TODO this will have to be changed once we remove this hard loop		
		//need user input to get name
	
	//TODO need to cleanup reset it draws wierd full health on start
	clear_all();

	//void* result;
	//if (pthread_join(t0, &result) == -1) {
	//	puts("error joining");
	//}

}



void play_game(difficulty _difficulty)
{
	set_difficulty(_difficulty);
	if(game_sequence == 0) init_game();
	run_game();
	game_sequence++;
}

void* stars(ALLEGRO_THREAD* thread, void* arg) {
	int i;
	bool* is_ready = (bool*)arg;

	for (i = 0; i < 50; i++) {
		_points.push_back(staticdisplayfactory::create_point(rand() % SCREEN_HEIGHT, rand() % SCREEN_WIDTH));
	}
	
	*is_ready = true;
	float rate = 10.0;
	float y_position;
	must_init(al_init_primitives_addon(), "primitives");
	while (!al_get_thread_should_stop(thread)) {

		
		int x, y;

		for (i = 0; i < _points.size(); i++) {
			y_position = _points[i]->get_y_position();
			if(y_position > SCREEN_HEIGHT)
				_points[i]->set_y_position(0);
			
			_points[i]->increment_y_pos(rate);
		}
		al_rest(0.04);

	}

	return NULL;

}
