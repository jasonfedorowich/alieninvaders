#include "background.h"


background::background(staticdisplaybuilder* builder) : staticdisplayobject(builder)
{

}


background::background()
{
}


background::~background()
{
	//al_destroy_bitmap(background_bitmap);
}

void background::draw()
{
	staticdisplayobject::draw();

	
}

