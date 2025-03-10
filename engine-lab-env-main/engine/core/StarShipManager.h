#pragma once
class StarShipManager
{
private:
	const int respawnTime = 300*5;
	int playerRespawnTimer = 0;
public:
	bool CountDown();
	static StarShipManager* instance();
};
#define startshipManager StarShipManager::instance()
