#include "colliderfactory.h"
#include "blast.h"




colliderfactory::colliderfactory()
{

}


colliderfactory::~colliderfactory()
{
	
}

twodcolliderbody* colliderfactory::create_2d_collider(float x, float y, int dmg, const char* image)
{
	colliderbodybuilder* builder = new colliderbodybuilder();
	builder->pos_x(x)->pos_y(y)->sizex(blast::blast_size_x)->sizey(blast::blast_size_y);	
	builder->set_damage(dmg)->set_image(image);

	blast* _blast = (blast*)builder->build_blast();
	delete builder;
	return _blast;
}
