#include "config.h"
#include "ParticleComponent.h"

#include "core/transform.h"
void ParticleComponent::Update(double dt) {
	const float thrusterPosOffset = 0.365f;
	((ParticleComponent*)owner->FindComponent(PARTICLEEMITTER, 0))->emiter->data.origin = glm::vec4(glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->position + (glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform[0]) * -thrusterPosOffset)) + (glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform[2]) * emitterOffset), 1);
	((ParticleComponent*)owner->FindComponent(PARTICLEEMITTER, 0))->emiter->data.dir = glm::vec4(glm::vec3(-((Transform*)owner->FindComponent(TRANSFORM))->transform[2]), 0);
	((ParticleComponent*)owner->FindComponent(PARTICLEEMITTER, 1))->emiter->data.origin = glm::vec4(glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->position + (glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform[0]) * thrusterPosOffset)) + (glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform[2]) * emitterOffset), 1);
	((ParticleComponent*)owner->FindComponent(PARTICLEEMITTER, 1))->emiter->data.dir = glm::vec4(glm::vec3(-((Transform*)owner->FindComponent(TRANSFORM))->transform[2]), 0);

	float t = currentSpeed /normalSpeed;
	((ParticleComponent*)owner->FindComponent(PARTICLEEMITTER, 0))->emiter->data.startSpeed = 1.2 + (3.0f * t);
	((ParticleComponent*)owner->FindComponent(PARTICLEEMITTER, 0))->emiter->data.endSpeed = 0.0f + (3.0f * t);
	((ParticleComponent*)owner->FindComponent(PARTICLEEMITTER, 1))->emiter->data.startSpeed = 1.2 + (3.0f * t);
	((ParticleComponent*)owner->FindComponent(PARTICLEEMITTER, 1))->emiter->data.endSpeed = 0.0f + (3.0f * t);
}
