#include "spritefactory.h"
#include "enemy.h"


spritefactory::spritefactory()
{
}


spritefactory::~spritefactory()
{
}

sprite* spritefactory::create_generic_enemy(int x_limit)
{
	int x = rand() % x_limit;

	spritebuilder objectbuilder2;
	objectbuilder2.pos_x(x)->pos_y(-10)->sizex(128.0)->sizey(128.0)->sorting_layer(1);
	objectbuilder2.set_health(50)->set_animation((*enemy::_animations)[1])->set_damage(enemy::damage);
	enemy* _enemy = (enemy*)objectbuilder2.build_computer();
	return _enemy;
}
