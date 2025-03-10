#pragma once
#include "physics.h"
#include "core/Entity.h"
namespace Component {

	class CollisionMesh : public ComponentBase
	{
	public:
		glm::vec3 colliderEndPoints[17];
		bool collisionCheck = false;
		Entity* owner;
		Physics::ColliderId colliderID;
		uint32_t id();
		void Update(double dt);
		void Start() { type = COLLISIONMESH; }
		bool CheckCollisions();
		~CollisionMesh();
	};
}

