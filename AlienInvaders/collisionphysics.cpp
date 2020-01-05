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

int collisionphysics::evaluate(void* arg1, void* arg2, void* arg3, void* action(void*, void*))
{
	int dmg;
	
	twodcolliderbody* _collider;
	sprite* _sprite = (sprite*)arg1;
	std::vector<twodcolliderbody*>* colliders = (std::vector<twodcolliderbody*>*) arg2;
	std::vector<staticdisplayobject*>* _explosions = (std::vector<staticdisplayobject*>*) arg3;
	int number_of_collisions = 0;
	int i, j;
//	std::vector<int> sprites_to_remove;
//	std::vector<int> collider_to_remove;

	//TODO change this as its resizing to much
	try {
		for (j = colliders->size() - 1; j >= 0; j--) {
			if (is_collision(_sprite->get_collider(), (*colliders)[j]->get_collider())) {
					
				_collider = (*colliders)[j];
				if (!_collider)
					throw std::exception("Cannot get a collider at location: " + j);
								
				dmg = _collider->get_damage();

				if (!_sprite->take_damage(dmg)) {
					_explosions->push_back(_sprite->explode());
					//sprites_to_remove.push_back(j);
					number_of_collisions += 10;
				}
					
				if (!_collider->is_invulerable()) {
					_explosions->push_back(_collider->explode());
					colliders->erase(colliders->begin() + j);
					delete _collider;
				}
					
				//delete _blast;
				//	collider_to_remove.push_back(i);
				if(action!=NULL)
					action(_sprite, _collider);
				number_of_collisions++;
				break;

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

