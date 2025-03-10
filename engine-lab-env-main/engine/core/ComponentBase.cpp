#include "config.h"
#include "ComponentBase.h"
//PoolAllocator Component::ComponentBase::allocator{ 1 };
//
//void* Component::ComponentBase::operator new(size_t size) {
//	return allocator.Allocate(size);
//}
//
//void Component::ComponentBase::operator delete(void* ptr, size_t size) {
//	return allocator.Deallocate(ptr, size);
//}

void ComponentId::CreateId(Component::ComponentBase* component) {
	if (nextValidid == component->ID) {
		idpool.insert(std::pair<int32, Component::ComponentBase*>(component->ID, component));
		nextValidid++;
		currentId++;
	}
	else
	{
		component->ID = nextValidid;
		nextValidid++;
		currentId++;
		idpool.insert(std::pair<int32, Component::ComponentBase*>(component->ID, component));
	}

}

void ComponentId::RemoveId(int32 id) {
	idpool.erase(id);
}

bool  ComponentId::IsValid(int32 id) {
	return idpool.contains(id);
}

Component::ComponentBase* ComponentId::FindComponent(int32 id) {
	if (idpool.contains(id)) {
		return idpool[id];
	}
	else
	{
		return NULL;
	}
}

ComponentId* ComponentId::Instance() {
	static ComponentId instance;
	return &instance;
}