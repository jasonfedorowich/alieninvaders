#pragma once
#include <allegro5/allegro_primitives.h>
#include <vector>

class animation
{
private:
	int position;
	float x, y;
	std::vector<ALLEGRO_BITMAP*> bitmaps;

public:
	animation();
	~animation();

	animation(std::vector<ALLEGRO_BITMAP*> bitmaps);
	void set_position(float, float);
	float get_x_position();
	float get_y_position();
	void animate();
};

