#include "sortingphysics.h"
#include "Sprite.h"



sortingphysics::sortingphysics()
{
}


sortingphysics::~sortingphysics()
{
}

//TODO need to change this to add enemy interaction
int sortingphysics::evaluate(void* arg1, void* arg2, void* arg3, void* action(void*, void*))
{
	bool* same_layer;
	try {
		sprite* _spriteA = (sprite*)arg1;
		std::vector<sprite*>* _sprites = (std::vector<sprite*>*) arg2;
		same_layer = (bool*)arg3;
		sprite* _spriteB;

		for (int i = 0; i < _sprites->size(); i++) {
			_spriteB = (*_sprites)[i];
			if (_spriteB->get_sorting_layer() == _spriteA->get_sorting_layer())
				if (_spriteA!= _spriteB && is_collision(((*_sprites)[i])->get_collider(), _spriteA->get_collider())) {
					if(action!=NULL)
						action(_spriteA, _spriteB);
					*same_layer = true;
					return 1;
				}

		}
	}
	catch (std::exception e) {
		throw std::exception(e.what());
	}
	
	return 0;
}
