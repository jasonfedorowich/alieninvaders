#include "staticdisplayobject.h"
#pragma once
class staticdisplayfactory
{
public:
	staticdisplayfactory();
	~staticdisplayfactory();
	static staticdisplayobject* create_explosion(float, float, float, float, const char*);
	static staticdisplayobject* create_explosion(float, float, const char*);
	static staticdisplayobject* create_point(float, float);
};

