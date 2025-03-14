#pragma once
#include <vector>
#include "vec3.hpp"
struct Node
{
	std::vector<Node*> neighBours;
	glm::vec3 position;
};

