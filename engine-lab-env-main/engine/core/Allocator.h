#pragma once
#include <vector>
using namespace std;
template <typename T, int size = 512> class Allocator
{
private:
	int sizeAllocated = size;
public:
	std::vector<T*> allocatedSpace;
	Allocator() { allocatedSpace.reserve(size); }
	void AddItem(T* item){ allocatedSpace.push_back(item); }
	void RemoveItem(int i){ allocatedSpace.erase(allocatedSpace.begin() + i); }
	int Size() { return sizeAllocated; }
};
