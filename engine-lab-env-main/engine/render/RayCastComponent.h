#pragma once
#include "core/Entity.h"
#include "physics.h"
namespace Component {
class RayCastComponent : public ComponentBase
{
	float length;
	glm::vec3 currentPos;
	glm::vec3 currentPos2;
	float currentLength = 0;
public:
	int mask = 1;
	Physics::RaycastPayload raycast2;
	glm::vec3 dir;
	bool sendCast = false;
	glm::vec3 pos;
	Entity* owner;
	bool slowMovingRay = false;
	Physics::RaycastPayload raycast;
	uint32_t id() { return 0; }
	void Update(double dt);
	void Start() { type = RAYCAST; }
	~RayCastComponent(){}
	void AddRayCast(glm::vec3 pos, glm::vec3 dir, float len);
};

}

