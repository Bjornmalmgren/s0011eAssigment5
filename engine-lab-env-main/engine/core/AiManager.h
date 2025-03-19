#pragma once
#include "core/Entity.h"
#include "core/AiMovement.h"

struct Respawn {
public:
	int respawn = 0;
	MovementType aiType;
	glm::vec4 color;
	int nearestNode = 0;
	bool respawnBool = false;
	Respawn() {}
};

class AiManager
{
	const int respawnTimer = 500;
public:
	std::vector<Respawn> respawnvector;
	bool respawn1 = false;
	static AiManager* instance();
	Respawn Respawn();
	void ClearUpVector();
};
#define AIManager AiManager::instance()

