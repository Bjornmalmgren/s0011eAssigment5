#pragma once
#include "core/Entity.h"
#include "render/input/inputserver.h"
namespace Component {

class InputComponent : public ComponentBase
{
public:
	const float normalSpeed = 1.0f;
	const float boostSpeed = normalSpeed * 2.0f;
	const float accelerationFactor = 1.0f;
	float currentSpeed = 0.0f;
	float rotX;
	float rotZ;
	float rotY;
	Entity* owner;
	glm::vec3 linearVelocity = glm::vec3(0);
	int ID;
	uint32_t id() { return 0; }
	void Update(double dt);
	void Start() { type = INPUT; }
	~InputComponent(){}
};

}

