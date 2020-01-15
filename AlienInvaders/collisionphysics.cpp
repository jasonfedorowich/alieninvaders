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
								
				
				if (!_collider->is_invulerable()) {
					colliders->erase(colliders->begin() + j);
				}
				if (action != NULL)
					action(_sprite, _collider);

				//delete _blast;
				//	collider_to_remove.push_back(i);
				
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

