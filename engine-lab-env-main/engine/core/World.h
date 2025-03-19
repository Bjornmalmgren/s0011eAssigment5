#pragma once
#include "core/Allocators.h"

#include <vector>
#include "core/StarShipManager.h"

class World
{
	//component allocators
public:
	std::vector<Entity*> entitys;
	
	Entity* player;
	int activeCameras = 0;
	int activeCamera = 0;
	Entity* FindEntity(int id);
	bool respawnPlayer;
	World();
	void CreateEntity();
	void AddEntity(Entity* ent);
	void UpdateEntitys(double dt);
	void StartEntitys();
	void AddComponent(ComponentBase* component, int id);
	void CreateSpaceShip();
	void CreateAISpaceShip(int, MovementType, glm::vec4 color);
	ComponentBase* FindEmptyComponent(ComponentTypes type);
};

