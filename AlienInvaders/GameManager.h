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
#include "background.h"
#include "twodcolliderbody.h"
#include "enemy.h"
#include "explosion.h"
#include "physicsengine.h"
#include "GameManager.h"
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

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000


std::string format_string(int score, char pad_with, int number_to_pad_to) {
	std::ostringstream out;
	out << std::internal << std::setfill(pad_with) << std::setw(number_to_pad_to) << score;
	return out.str();
}