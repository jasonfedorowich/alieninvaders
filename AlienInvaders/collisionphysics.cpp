#include "collisionphysics.h"
#include "Sprite.h"
#include "twodcolliderbody.h"
#include <iostream>



collisionphysics::collisionphysics()
{
}


collisionphysics::~collisionphysics()
{
}

int collisionphysics::evaluate(void* arg1, void* arg2, void* arg3)
{
	int dmg;
	sprite* _sprite;
	twodcolliderbody* _collider;

	std::vector<sprite*>* sprites = (std::vector<sprite*>*) arg1;
	std::vector<twodcolliderbody*>* colliders = (std::vector<twodcolliderbody*>*) arg2;
	std::vector<staticdisplayobject*>* _explosions = (std::vector<staticdisplayobject*>*) arg3;
	int number_of_collisions = 0;
	int i, j;
//	std::vector<int> sprites_to_remove;
//	std::vector<int> collider_to_remove;

	//TODO change this as its resizing to much
	try {

		for (i = sprites->size() - 1; i >= 0; i--) {
			for (j = colliders->size() - 1; j >= 0; j--) {
				if (is_collision((*sprites)[i]->get_collider(), (*colliders)[j]->get_collider())) {
					
					_collider = (*colliders)[j];
					if (!_collider)
						throw std::exception("Cannot get a collider at location: " + j);
					
					_sprite = (*sprites)[i];
					if (!_sprite)
						throw std::exception("Cannot get a sprite at location: " + i);
					
					dmg = _collider->get_damage();

					if (!_sprite->take_damage(dmg)) {
						_explosions->push_back(_sprite->explode());
						sprites->erase(sprites->begin() + i);
						delete _sprite;
						//sprites_to_remove.push_back(j);
					}

					_explosions->push_back(_collider->explode());
					colliders->erase(colliders->begin() + j);
					delete _collider;
					//delete _blast;
				//	collider_to_remove.push_back(i);
					number_of_collisions++;
					break;

				}
			}

		}
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}

	//for (auto it = sprites_to_remove.begin(); it != sprites_to_remove.end(); it++) {
	//	sprites->erase(sprites->begin() + *it);
//		delete (*sprites)[*it];
//	}


//	for (auto it = collider_to_remove.begin(); it != collider_to_remove.end(); it++) {
//		colliders->erase(colliders->begin() + *it);
//		delete (*colliders)[*it];
	//}

	return number_of_collisions;
}

