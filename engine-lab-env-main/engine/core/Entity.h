#pragma once
#include "ComponentBase.h"
#include <vector>
#include <map>


using namespace Component;
struct Entity
{
	
public:
	//static PoolAllocator allo;
	/*static void* operator new(size_t size);
	static void operator delete(void* ptr, size_t size);*/
	int32_t id;
	std::vector<ComponentBase*> components;
	Entity();
	~Entity();
	bool Destroyed = false;
	ComponentBase* FindComponent(ComponentTypes type);
	ComponentBase* FindComponent(ComponentTypes type, int num);
	ComponentBase* FindComponent(int id);
	void Deallocate();
	Entity(int ID);
private:
};

class EntityId
{
public:
	void CreateId(Entity* entity);
	void RemoveId(int32 id);
	Entity* FindEntity(int32 id);
	bool IsValid(int32 id);
	static EntityId* Instance();

private:
	int32_t currentId = 0;
	int32_t nextValidid = 1;
	std::map<int32, Entity*> idpool;

};
#define entityID EntityId::Instance()