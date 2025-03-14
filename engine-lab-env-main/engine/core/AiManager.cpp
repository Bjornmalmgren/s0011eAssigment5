#include "config.h"
#include "AiManager.h"
AiManager* AiManager::instance() {
	static AiManager instance;
	return &instance;
}

bool AiManager::Respawn() {
	if (respawn >= respawnTimer) {
		return true;
	}
	else
	{
		respawn++;
		return false;
		//fix respawn
	}
}