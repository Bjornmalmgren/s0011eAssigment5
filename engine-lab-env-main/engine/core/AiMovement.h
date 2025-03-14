#pragma once
#include "Entity.h"
#include "render/NodeManager.h"
namespace Component {
	class AiMovement : public ComponentBase
	{
		const float accelerationFactor = 1.0f;
		const float normalSpeed = 1.0f;
	public:
		float currentSpeed = 0.0f;
		int slowing = 0;
		int nearNode = 0;
		glm::vec3 linearVelocity = glm::vec3(0);
		glm::vec3 linearVelocitys = glm::vec3(0);
		Entity* owner;
		Node* nextNode;
		Node* previousNode;
		Node* nearestNode;
		uint32_t id() { return 0; }
		void Update(double dt);
		void Start();
		void AssignNextNode(Node*);
		bool CheckPosition(glm::vec3);
		void LookAt();
	};
}


