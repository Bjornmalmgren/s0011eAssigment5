#pragma once
#include "core/Entity.h"
#include "render/particlesystem.h"
namespace Component {
	class ParticleComponent : public ComponentBase
	{
	public:
		const float normalSpeed = 1.0f;
		float currentSpeed = 0;
		float emitterOffset = -0.5f;
		Render::ParticleEmitter* emiter;
		int ID;
		Entity* owner;
		uint32_t id() { return 0; }
		void Update(double dt);
		void Start() { type = PARTICLEEMITTER; }
		~ParticleComponent(){}
		
	};
}


