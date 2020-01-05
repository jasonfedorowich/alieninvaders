#include "enemycontroller.h"
#include "enemy.h"



enemycontroller::enemycontroller()
{
}


enemycontroller::~enemycontroller()
{
}

void enemycontroller::move_sprite(void* arg1, float y_speed, float x_speed)
{
	try {
		enemy* _enemy = (enemy*)arg1;
		_enemy->move(y_speed);
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
		_enemy_blasts->push_back(_enemy->fire());
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}

}
