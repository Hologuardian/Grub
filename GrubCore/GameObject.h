#ifndef GRUB_GAMEOBJECT
#define GRUB_GAMEOBJECT
#include "Constants.h"
#include "GameComponent.h"
#include <vector>

class GameObject
{
public:
	GameObject(Matrix* transform)
	{
		GameObject::transform = transform;
	}
	~GameObject()
	{
		delete transform;
		transform = nullptr;
		delete components;
		components = nullptr;
	}
	Matrix* transform;
	std::vector<GameComponent*>* components;

public:
	void Update(float deltaTime)
	{
		for (int i = 0; i < components->size(); i++)
		{
			GameComponent* comp = components->at(i);
			comp->Update(deltaTime);
		}
	}

	void RegisterComponent(GameComponent* component)
	{
		components->push_back(component);
	}

	void RemoveComponent(GameComponent* component)
	{
		for (int i = 0; i < components->size(); i++)
		{
			GameComponent* comp = components->at(i);
			if (comp == component)
			{
				components->erase(components->begin() + i);
				return;
			}
		}
	}
};
#endif