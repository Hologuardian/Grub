#ifndef GRUB_GAMEOBJECT
#define GRUB_GAMEOBJECT
#include "Constants.h"

class GameObject
{
public:
	GameObject(Matrix* transform)
	{
		GameObject::transform = transform;
	}
	Matrix* transform;
};
#endif