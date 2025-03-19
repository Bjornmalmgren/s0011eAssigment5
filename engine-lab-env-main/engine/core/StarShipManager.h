#pragma once
#include "Entity.h"
class StarShipManager
{
private:
	const int respawnTime = 300;
	int playerRespawnTimer = 0;
public:
	bool drawRays = false;
	Entity* player;
	bool CountDown();
	static StarShipManager* instance();
};
#define startshipManager StarShipManager::instance()
