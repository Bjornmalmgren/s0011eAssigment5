#include "config.h"
#include "AiManager.h"
AiManager* AiManager::instance() {
	static AiManager instance;
	return &instance;
}

Respawn AiManager::Respawn() {
	
	for (int i = 0; i < respawnvector.size(); i++)
	{
		if (respawnvector[i].respawn >= respawnTimer) {
			respawnvector[i].respawnBool = true;
			return respawnvector[i];
		}
		respawnvector[i].respawn++;
	}
	return respawnvector[0];
}

void AiManager::ClearUpVector() {
	std::vector<int> index;
	for (int i = 0; i < respawnvector.size(); i++)
	{
		if (respawnvector[i].respawnBool == true) {
			index.push_back(i);
		}
	}
	for (int i = 0; i < index.size(); i++)
	{
		respawnvector.erase(respawnvector.begin() + index[i]);
	}
}