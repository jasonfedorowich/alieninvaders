#include "enemycontroller.h"
#include "enemy.h"



enemycontroller::enemycontroller()
{
}


enemycontroller::~enemycontroller()
{
}

void enemycontroller::move_sprite(void* arg1, void* arg2)
{
	try {
		enemy* _enemy = (enemy*)arg1;
		_enemy->move();
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}

}

void enemycontroller::fire(void* arg1, void* arg2)
{
	try {
		enemy* _enemy = (enemy*)arg1;
		std::vector<gameobject*>* _enemy_blasts = (std::vector <gameobject*>*) arg2;
		int random_chance = rand() % 10;
		if (random_chance == 1) {
			_enemy_blasts->push_back(_enemy->fire());
		}
		return;
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}

}
