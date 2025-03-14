#pragma once
#include "Node.h"
class NodeManager
{
public:
	std::vector<Node*> nodes;
	void DrawNodes(bool);
	void createNode(glm::vec3);
	bool draw = false;
	bool addNode = false;
	static NodeManager* Instance();
};
#define nodeMGR NodeManager::Instance()
