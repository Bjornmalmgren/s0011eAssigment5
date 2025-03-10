#pragma once
#include <vector>
#include "core/Entity.h"
using namespace std;
namespace Component {

	struct Transform : public ComponentBase
	{
	public:
		ComponentTypes type = TRANSFORM;
		Entity* owner;
		uint32_t id() override;
		glm::vec3 position = { 0,0,0 };
		glm::quat rotation;
		glm::vec3 scale = { 1,1,1 };
		glm::mat4 transform;
		void Update(double dt) {}
		void Start() { type = TRANSFORM; }
		~Transform();
	};
}
//class Matrix {
//	glm::mat4 matrix;
//	//Matrix(float xx, float xy, float xz, float xw, float yx, float yy, float yz, float yw, float zx, float zy, float zz, float zw, float wx, float wy, float wz, float ww);
//	Matrix();
//	~Matrix();
//	//Matrix ToMatrix(Transform transform);
//};

