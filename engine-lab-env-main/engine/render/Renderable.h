#pragma once
#include "model.h"
//#include "core/ComponentBase.h"
#include "core/Entity.h"
namespace Component {
	class Renderable : public ComponentBase
	{
		
	public:

		Entity* owner = NULL;
		Render::ModelId modelId = 0;
		Render::Model model;
		uint32_t id();
		void Update(double dt);
		void Start();
		Renderable();
		~Renderable();
	};
}


