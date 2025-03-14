#pragma once
//#include "PoolAllocator.h"
#include <map>
enum ComponentTypes
{
	TRANSFORM,
	CAMERA,
	RIGIDBODY,
	COLLISIONMESH,
	CONTINUESFORCE,
	RENDERABLE,
	AUDIOEMITER,
	PARTICLEEMITTER,
	LIGHTSOURCE,
	INPUT,
	RAYCAST,
	AIMOVEMENT,
};

namespace Component {
	class ComponentBase
	{
		
	public:
		ComponentTypes type;
		/*static PoolAllocator allocator;
		static void* operator new(size_t size);
		static void operator delete(void* ptr, size_t size);*/
		int ID;
		virtual uint32_t id() = 0;
		virtual void Update(double dt) = 0;
		virtual void Start() = 0;
		virtual ~ComponentBase() {};
	};


}
class ComponentId
{
public:
	void CreateId(Component::ComponentBase* component);
	void RemoveId(int32 id);
	Component::ComponentBase* FindComponent(int32 id);
	bool IsValid(int32 id);
	static ComponentId* Instance();

private:
	int32_t currentId = 0;
	int32_t nextValidid = 1;
	std::map<int32, Component::ComponentBase*> idpool;

};
#define componentID ComponentId::Instance()
