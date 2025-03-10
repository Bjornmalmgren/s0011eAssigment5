#include "config.h"
#include "Entity.h"
#include "core/transform.h"
#include "core/InputComponent.h"
#include "render/CameraComponent.h"
#include "render/CollisionMesh.h"
#include "render/ContinuesMovement.h"
#include "render/ParticleComponent.h"
#include "render/Renderable.h"
#include "render/particlesystem.h"
void EntityId::CreateId(Entity* entity) {
	if (nextValidid == entity->id) {
		idpool.insert(std::pair<int32, Entity*>(entity->id, entity));
		nextValidid++;
		currentId++;
	}
	else
	{
		entity->id = nextValidid;
		nextValidid++;
		currentId++;
		idpool.insert(std::pair<int32, Entity*>(entity->id, entity));
	}
	
}

void EntityId::RemoveId(int32 id) {
	idpool.erase(id);
}

bool EntityId::IsValid(int32 id) {
	return idpool.contains(id);
}

Entity* EntityId::FindEntity(int32 id) {
	if (idpool.contains(id)) {
		return idpool[id];
	}
	else
	{
		return NULL;
	}
}

EntityId* EntityId::Instance() {
	static EntityId instance;
	return &instance;
}

//void *Entity::operator new(size_t size) {
//	return allo.Allocate(size);
//}
//
//void Entity::operator delete(void* ptr, size_t size) {
//	return allo.Deallocate(ptr, size);
//}

Entity::Entity() {
	
}
Entity::~Entity() {

}

ComponentBase* Entity::FindComponent(ComponentTypes type) {
	for (auto comp : components)
	{
		if (comp->type == type) {
			return comp;
		}
	}
	return NULL;
}

ComponentBase* Entity::FindComponent(int id) {
	for (auto comp : components)
	{
		if (comp->ID == id) {
			return comp;
		}
	}
	return NULL;
}

ComponentBase* Entity::FindComponent(ComponentTypes type, int num) {
	int j = 0;
	ComponentBase* lastComponent = NULL;
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->type == type) {
			lastComponent = components[i];
			if (j == num) {
				return components[i];
			}
			else
			{
				j++;
			}
			
		}
	}
	if (lastComponent != NULL) {
		return lastComponent;
	}
	return NULL;
}

void Entity::Deallocate() {
	for (int i = 0; i < components.size(); i++)
	{
		switch (components[i]->type)
		{
		case TRANSFORM:
			((Transform*)components[i])->position = glm::vec3(0, 0, 0);
			((Transform*)components[i])->owner = NULL;
			((Transform*)components[i])->transform = glm::mat4(1);
			((Transform*)components[i])->rotation = glm::quat();

			break;
		case RENDERABLE:
			((Renderable*)components[i])->owner = NULL;
			break;
		case CAMERA:
			((CameraComponent*)components[i])->owner = NULL;

			
			break;
		case INPUT:
			((InputComponent*)components[i])->currentSpeed = 0;
			((InputComponent*)components[i])->linearVelocity = glm::vec3(0, 0, 0);
			((InputComponent*)components[i])->owner = NULL;
			((InputComponent*)components[i])->rotX = 0;
			((InputComponent*)components[i])->rotY = 0;
			((InputComponent*)components[i])->rotZ = 0;

			break;
		case COLLISIONMESH:
			((CollisionMesh*)components[i])->owner = NULL;
			((CollisionMesh*)components[i])->collisionCheck = false;
			break;
		case PARTICLEEMITTER:

			Render::ParticleSystem::Instance()->RemoveEmitter(((ParticleComponent*)components[i])->emiter);
			((ParticleComponent*)components[i])->emiter = NULL;	
			((ParticleComponent*)components[i])->owner = NULL;
			
			break;
		case CONTINUESFORCE:
			((ContinuesMovement*)components[i])->move = false;
			((ContinuesMovement*)components[i])->owner = NULL;
			((ContinuesMovement*)components[i])->rotationZ = 0;
			((ContinuesMovement*)components[i])->rotX = 0;
			((ContinuesMovement*)components[i])->rotXSmooth = 0;
			((ContinuesMovement*)components[i])->rotY = 0;
			((ContinuesMovement*)components[i])->rotYSmooth = 0;
			((ContinuesMovement*)components[i])->rotZ = 0;
			((ContinuesMovement*)components[i])->rotZSmooth = 0;
			break;

		default:
			break;
		}
	}
	components.clear();
	Destroyed = true;
}
