#include "spritefactory.h"
#include "enemy.h"


spritefactory::spritefactory()
{
}


spritefactory::~spritefactory()
{
}

sprite* spritefactory::create_generic_enemy(float x, float y, void* arg)
{
	spritebuilder* _spritebuilder = (spritebuilder*)arg;
	_spritebuilder->pos_x(x)->pos_y(y);
	return (enemy*)_spritebuilder->build_computer();
}
