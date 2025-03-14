#pragma once
#include "render/CollisionMesh.h"
#include "render/Renderable.h"
#include "core/transform.h"
#include "render/ContinuesMovement.h"
#include "render/ParticleComponent.h"
#include "core/InputComponent.h"
#include "render/CameraComponent.h"
#include <vector>
#include "core/StarShipManager.h"
#include "render/RayCastComponent.h"
#include "core/AiMovement.h"
#include "Allocator.h"
class World
{
	//component allocators
public:
	std::vector<Entity*> entitys;
	Allocator<Component::Renderable, 1024> renderableAllocator;
	Allocator<Component::Transform, 1024> transformAllocator;
	Allocator<Component::CollisionMesh, 1024> collisionAllocator;
	Allocator<Component::ContinuesMovement, 1024> cmovementAllocator;
	Allocator<Component::ParticleComponent, 1024> particleAllocator;
	Allocator<Component::RayCastComponent, 500> raycastAllocator;
	Allocator<Component::AiMovement, 100> aiAllocator;
	Allocator<Component::InputComponent, 1> inputAllocator;
	Allocator<Component::CameraComponent, 5> cameraAllocator;
	Allocator<Entity, 1024> entityAllocator;
	Entity* player;
	Entity* FindEntity(int id);
	bool respawnPlayer;
	World();
	void CreateEntity();
	void AddEntity(Entity* ent);
	void UpdateEntitys(double dt);
	void StartEntitys();
	void AddComponent(ComponentBase* component, int id);
	void CreateSpaceShip();
	void CreateAISpaceShip();
	ComponentBase* FindEmptyComponent(ComponentTypes type);
};

