#include "config.h"
#include "RayCastComponent.h"
#include "core/transform.h"
#include "render/debugrender.h"
#include "core/Allocators.h"
void RayCastComponent::Update(double dt) {
	
	
	if (slowMovingRay == false) {
		glm::vec3 pos2;
		if (pos.x != 0 || pos.y != 0 || pos.z != 0) {
			glm::vec3 poss = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(pos), 0.0f);
			poss.x *= 1.5;
			poss.y *= 1.5;
			poss.z *= 1.5;
			pos2 = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss;
		}
		else
		{
			pos2 = ((Transform*)owner->FindComponent(TRANSFORM))->position;
		}

		glm::vec3 dir = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(this->dir, 0);
		if (mask > 0) {
			raycast = Physics::Raycast(pos2, dir, length, mask);
		}
		else
		{
			raycast = Physics::Raycast(pos2, dir, length);
		}
		
		if (owner->drawRaycasts) {
			Debug::DrawLine(pos2, pos2 + dir * length, 1.0f, glm::vec4(1, 0, 1, 1), glm::vec4(1, 0, 1, 1), Debug::RenderMode::Normal);
		}
		
	}
	else if (slowMovingRay == true && sendCast == true) {
		glm::vec3 pos2;
		
		if (pos.x != 0 || pos.y != 0 || pos.z != 0) {
			glm::vec3 poss = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(pos), 0.0f);
			poss.x *= 1.5;
			poss.y *= 1.5;
			poss.z *= 1.5;
			pos2 = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss;
		}
		else
		{
			pos2 = ((Transform*)owner->FindComponent(TRANSFORM))->position;
		}
		currentPos = pos2;
		//glm::vec3 dir = ((Transform*)owner->FindComponent(TRANSFORM))->transform  * glm::vec4(this->dir,0);
		glm::vec3 v = this->dir;
		currentPos += v*currentLength;
		currentLength +=1;
		raycast = Physics::Raycast(currentPos, dir, 2);
		if (owner->drawRaycasts) {
			Debug::DrawLine(currentPos, currentPos + dir * 2.0f, 1.0f, glm::vec4(1, 1, 0, 1), glm::vec4(1, 1, 0, 1), Debug::RenderMode::Normal);
		}
		if (currentLength >= length) {
			//max length reached
			sendCast = false;
			currentLength = 0;
		}
		if (raycast.hit ) {

			int j = 2;
			//raycast.collider
			for (int i = 0; i < allo->collisionAllocator.allocatedSpace.size(); i++)
			{
				if (raycast.collider.index == allo->collisionAllocator.allocatedSpace[i]->colliderID.index) {
					if (allo->collisionAllocator.allocatedSpace[i]->owner != NULL) {

						if (allo->collisionAllocator.allocatedSpace[i]->owner->spaceshipType != NONE) {
							allo->collisionAllocator.allocatedSpace[i]->owner->Deallocate();
						}
					}
					
					
					
					


				}
			}
			
		}

		glm::vec3 pos3;

		if (pos.x != 0 || pos.y != 0 || pos.z != 0) {
			glm::vec3 poss3 = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(glm::vec3(-pos.x, pos.y, pos.z)), 0.0f);
			poss3.x *= 1.5;
			poss3.y *= 1.5;
			poss3.z *= 1.5;
			pos3 = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss3;
		}
		else
		{
			pos3 = ((Transform*)owner->FindComponent(TRANSFORM))->position;
		}
		currentPos2 = pos3;
		//glm::vec3 dir = ((Transform*)owner->FindComponent(TRANSFORM))->transform  * glm::vec4(this->dir,0);

		currentPos2 += v * currentLength;
		currentLength +=1;
		raycast2 = Physics::Raycast(currentPos2, dir, 2);
		if (owner->drawRaycasts) {
			Debug::DrawLine(currentPos2, currentPos2 + dir * 2.0f, 1.0f, glm::vec4(1, 1, 0, 1), glm::vec4(1, 1, 0, 1), Debug::RenderMode::Normal);
		}
		if (currentLength >= length) {
			//max length reached
			sendCast = false;
			currentLength = 0;
		}
		if (raycast2.hit) {

			int j = 2;
			//raycast.collider
			for (int i = 0; i < allo->collisionAllocator.allocatedSpace.size(); i++)
			{
				if (raycast2.collider.index == allo->collisionAllocator.allocatedSpace[i]->colliderID.index) {
					if (raycast.hit == false&& allo->collisionAllocator.allocatedSpace[i]->owner != NULL) {
						if (allo->collisionAllocator.allocatedSpace[i]->owner->spaceshipType != NONE) {
							allo->collisionAllocator.allocatedSpace[i]->owner->Deallocate();
						}
						
					}
					




				}
			}

		}
		
	}
	
	
}

void RayCastComponent::AddRayCast(glm::vec3 pos, glm::vec3 dir, float len) {
	raycast = Physics::Raycast(pos, dir, len);
	length = len;
	this->dir = dir;

}
