#pragma once
#include "GameManager.h"
#include "gui.h"
#include "staticdisplayobject.h"

static bool start_screen_running;
static bool difficulty_screen_running;
static bool game_is_running;
static ALLEGRO_DISPLAY* display = NULL;
static bool running;
static difficulty _difficulty = difficulty::NONE;


int main();



void* easy_button_fn(void*, void*) {
	difficulty_screen_running = false;
	_difficulty = difficulty::EASY;
	return NULL;
}

void* hard_button_fn(void*, void*) {
	difficulty_screen_running = false;
	_difficulty = difficulty::HARD;
	return NULL;
}

void* hardcore_button_fn(void*, void*) {
	difficulty_screen_running = false;
	_difficulty = difficulty::HARDCORE;
	return NULL;
}

void* start_button_function_up(void*, void*) {
	start_screen_running = false;
	return NULL;
}

void* null_function(void*, void*) {
	return NULL;
}

void* done_function(void*, void*) {
	running = false;
	return NULL;
}

void* overall_done_func(void*, void*) {
	game_is_running = false;
	running = false;
	return NULL;
}