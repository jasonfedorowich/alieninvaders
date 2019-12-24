#pragma once
class boxcollider
{
private:
	float width, height;
	float x, y;
public:
	boxcollider();
	~boxcollider();
	boxcollider(float, float);
	void set_position(float, float);
	float get_x_position();
	float get_y_position();
	float get_height();
	float get_width();
};

bool is_collision(boxcollider* box1, boxcollider* box2);
