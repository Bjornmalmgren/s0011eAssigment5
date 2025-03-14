#pragma once
#include "core/Entity.h"
class AiManager
{
	const int respawnTimer = 500;
	int respawn = 0;
public:
	bool respawn1 = false;
	Entity* AI1;
	static AiManager* instance();
	bool Respawn();
};
#define AIManager AiManager::instance()

