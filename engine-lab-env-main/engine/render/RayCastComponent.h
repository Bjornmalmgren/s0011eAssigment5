#pragma once
#include "core/Entity.h"
#include "physics.h"
namespace Component {
class RayCastComponent : public ComponentBase
{
	glm::vec3 dir;
	float length;
public:
	glm::vec3 pos;
	Entity* owner;
	Physics::RaycastPayload raycast;
	uint32_t id() { return 0; }
	void Update(double dt);
	void Start() { type = RAYCAST; }
	~RayCastComponent(){}
	void AddRayCast(glm::vec3 pos, glm::vec3 dir, float len);
};

}

