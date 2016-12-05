#ifndef GRUB_GAMECOMPONENT
#define GRUB_GAMECOMPONENT
class GameObject;

class GameComponent
{
public:
	GameObject* parent;
public:
	GameComponent(GameObject* object)
	{
		parent = object;
	}

	virtual void Update(float deltaTime) = 0;
};
#endif