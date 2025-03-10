#pragma once
#include "core/Entity.h" 
namespace Component {
	class ContinuesMovement : public ComponentBase
	{
	private:
		int rotationDir;

	public:
		float rotX = 0;
		float rotY = 0;
		float rotZ = 0;
		Entity* owner;
		bool move = false;
		void Movement(double dt);
		float rotationZ = 0;
		float rotXSmooth = 0;
		float rotYSmooth = 0;
		float rotZSmooth = 0;
		int ID;
		uint32_t id() { return 0; }
		void Update(double dt);
		void Start();
		~ContinuesMovement(){}
	};
}


