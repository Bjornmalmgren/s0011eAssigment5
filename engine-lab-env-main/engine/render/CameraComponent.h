#pragma once
#include "core/Entity.h"
#include "render/cameramanager.h"
namespace Component {

class CameraComponent : public ComponentBase
{
	glm::vec3 camPos = glm::vec3(0, 1.0f, -2.0f);
	const float camOffsetY = 1.0f;
	float camOffsetX = 0.0f;
	float camOffsetZ = -4.0f;
	bool moveCamera = false;
public:
	const float cameraSmoothFactor = 10.0f;
	Render::Camera* cam = Render::CameraManager::GetCamera(CAMERA_MAIN);
	Entity* owner;
	uint32_t id() { return 0; }
	void Update(double dt);
	void Start() { type = CAMERA; }
	~CameraComponent(){}
};
}

