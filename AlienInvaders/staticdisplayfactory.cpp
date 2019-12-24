#include "staticdisplayfactory.h"
#include "explosion.h"



staticdisplayfactory::staticdisplayfactory()
{
}


staticdisplayfactory::~staticdisplayfactory()
{
}

staticdisplayobject* staticdisplayfactory::create_explosion(float x, float y, float factor_x, float factor_y, const char* img)
{
	staticdisplaybuilder* builder = new staticdisplaybuilder();
	builder->pos_x(x)->pos_y(y);
	builder->base_x_factor(factor_x)->base_y_factor(factor_y)->image(img)->is_drawn(false);

	explosion* _explosion = (explosion*) builder->build_explosion();
	delete builder;
	return _explosion;
}

staticdisplayobject* staticdisplayfactory::create_explosion(float x, float y, const char* img) {
	staticdisplaybuilder* builder = new staticdisplaybuilder();
	builder->pos_x(x)->pos_y(y);
	builder->image(img)->is_drawn(false);
	explosion* _explosion = (explosion*)builder->build_explosion();
	delete builder;
	return _explosion;
}

staticdisplayobject* staticdisplayfactory::create_point(float x, float y)
{
	staticdisplaybuilder* builder = new staticdisplaybuilder();
	builder->pos_x(x)->pos_y(y);
	staticdisplayobject* _point = (staticdisplayobject*) builder->build();
	delete builder;
	return _point;
}
