#include "config.h"
#include "NodeManager.h"
#include "render/debugrender.h"
void NodeManager::DrawNodes(bool draw) {
	if (draw == true) {
		for (int i = 0; i < nodes.size(); i++)
		{
			//up
			Debug::DrawLine(glm::vec3(nodes[i]->position.x, nodes[i]->position.y, nodes[i]->position.z), glm::vec3(nodes[i]->position.x, nodes[i]->position.y + 1, nodes[i]->position.z), 1 , glm::vec4(1, 0, 0, 1), glm::vec4(1, 0, 0, 1), Debug::RenderMode::Normal);
			//down
			Debug::DrawLine(glm::vec3(nodes[i]->position.x, nodes[i]->position.y, nodes[i]->position.z), glm::vec3(nodes[i]->position.x, nodes[i]->position.y - 1, nodes[i]->position.z), 1, glm::vec4(1, 0, 0, 1), glm::vec4(1, 0, 0, 1), Debug::RenderMode::Normal);

			Debug::DrawLine(glm::vec3(nodes[i]->position.x, nodes[i]->position.y, nodes[i]->position.z), glm::vec3(nodes[i]->position.x, nodes[i]->position.y , nodes[i]->position.z + 1), 1, glm::vec4(0, 0, 1, 1), glm::vec4(0, 0, 1, 1), Debug::RenderMode::Normal);
			Debug::DrawLine(glm::vec3(nodes[i]->position.x, nodes[i]->position.y, nodes[i]->position.z), glm::vec3(nodes[i]->position.x, nodes[i]->position.y, nodes[i]->position.z - 1), 1, glm::vec4(0, 0, 1, 1), glm::vec4(0, 0, 1, 1), Debug::RenderMode::Normal);

			Debug::DrawLine(glm::vec3(nodes[i]->position.x, nodes[i]->position.y, nodes[i]->position.z), glm::vec3(nodes[i]->position.x+1, nodes[i]->position.y, nodes[i]->position.z ), 1, glm::vec4(0, 1, 0, 1), glm::vec4(0, 1, 0, 1), Debug::RenderMode::Normal);
			Debug::DrawLine(glm::vec3(nodes[i]->position.x, nodes[i]->position.y, nodes[i]->position.z), glm::vec3(nodes[i]->position.x-1, nodes[i]->position.y, nodes[i]->position.z ), 1, glm::vec4(0, 1, 0, 1), glm::vec4(0, 1, 0, 1), Debug::RenderMode::Normal);
			
			for (int j = 0; j < nodes[i]->neighBours.size(); j++)
			{
				Debug::DrawLine(nodes[i]->position, nodes[i]->neighBours[j]->position, 1.5f, glm::vec4(0.5, 0, 1, 1), glm::vec4(0.5, 0, 1, 1), Debug::RenderMode::Normal);
			}
		}

	}
}
NodeManager* NodeManager::Instance() {
	static NodeManager nmgr;
	return &nmgr;
}

void NodeManager::createNode(glm::vec3 v) {
	Node* n = new Node();
	n->position = v;
	n->position = v;
	nodes.push_back(n);
}