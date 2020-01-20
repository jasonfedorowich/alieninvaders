#pragma once
#include <cstddef>
#include <stdio.h>
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/color.h"
#include <allegro5/allegro5.h>
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include "allegro5/color.h"
#include <allegro5/allegro_primitives.h>
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/color.h"
#include "ship.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "blast.h"
#include <iostream>
#include "twodcolliderbody.h"
#include "enemy.h"
#include "explosion.h"
#include "physicsengine.h"
#include "staticdisplayfactory.h";
#include "spritefactory.h"
#include <Windows.h>
#include <sstream>
#include "controller.h"
#include "enemycontroller.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "score.h"
#include "constants.h"
#include "healthbar.h"
#include "difficulty.h"
#include <chrono>
#include "gui.h"
#include "behaviour.h"
#include "heart.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
static const std::string DEFAULT_HEALTH_BAR_SETTINGS_LOCATION = "../resources/gamedata/constants/healthbar.xml";
static const std::string DEFAULT_GAME_SETTINGS_LOCATION = "../resources/gamedata/constants/constants.xml";


void init_allegro();
ALLEGRO_DISPLAY* get_display();
ALLEGRO_TIMER* get_timer();
void play_game(difficulty);
void shut_down_allegro();
int get_score();
void destroy();
void add_behaviour(behaviour*);
void clear_score();