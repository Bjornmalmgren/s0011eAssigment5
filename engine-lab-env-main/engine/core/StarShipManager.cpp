#include "config.h"
#include "StarShipManager.h"
bool StarShipManager::CountDown() {
	if (playerRespawnTimer >= respawnTime) {
		playerRespawnTimer = 0;
		return true;
	}
	playerRespawnTimer += 1;
	return false;
}

StarShipManager* StarShipManager::instance() {
	static StarShipManager startShip;
	return &startShip;
}