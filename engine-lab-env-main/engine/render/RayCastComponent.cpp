#include "config.h"
#include "RayCastComponent.h"
#include "core/transform.h"
#include "render/debugrender.h"
void RayCastComponent::Update(double dt) {
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
	
	glm::vec3 dir = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(this->dir,0);
	raycast = Physics::Raycast(pos2, dir, length);
		
	Debug::DrawLine(pos2, pos2 + dir * (length/2), 1.0f, glm::vec4(1, 0, 1, 1), glm::vec4(1, 0, 1, 1), Debug::RenderMode::Normal);
	
}

void RayCastComponent::AddRayCast(glm::vec3 pos, glm::vec3 dir, float len) {
	raycast = Physics::Raycast(pos, dir, len);
	length = len;
	this->dir = dir;

}
