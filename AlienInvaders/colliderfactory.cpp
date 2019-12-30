#include "colliderfactory.h"
#include "blast.h"




colliderfactory::colliderfactory()
{

}


colliderfactory::~colliderfactory()
{
	
}

twodcolliderbody* colliderfactory::create_2d_collider(float x, float y, void* arg)
{
	colliderbodybuilder* _colliderbuilder = (colliderbodybuilder*)arg;
	_colliderbuilder->pos_x(x)->pos_y(y);
	return _colliderbuilder->build_blast();
}
