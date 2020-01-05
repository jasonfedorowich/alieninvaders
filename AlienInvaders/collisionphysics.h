#pragma once
#include "physics.h"
class collisionphysics :
	public physics
{
public:
	collisionphysics();
	virtual ~collisionphysics();

	virtual int evaluate(void*, void*, void*, void* action(void*, void*)) override;
	//template<typename T, typename U, typename V>
	//T evaluate(U*, V*) override;
	//template<class T, class U, class V >
//	std::vector<gameobject*> evaluate <std::vector<gameobject*>, std::vector<gameobject*>*, std::vector<gameobject*>*>(std::vector<gameobject*>*, std::vector<gameobject*>*) override;

	// template std::vector<gameobject*>  evaluate <std::vector<gameobject*>, std::vector<gameobject*>*, std::vector<gameobject*>*> (std::vector<gameobject*>*, std::vector<gameobject*>*);
};


