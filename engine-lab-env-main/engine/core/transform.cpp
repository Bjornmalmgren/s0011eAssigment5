#include "config.h"
#include "transform.h"

uint32_t Component::Transform::id() {
	return 0;
}
Component::Transform::~Transform() {

}
//Matrix::Matrix() {
//	matrix[0][0] = 1;
//	matrix[1][1] = 1;
//	matrix[2][2] = 1;
//	matrix[3][3] = 1;
//}

//Matrix::Matrix(float xx, float xy, float xz, float xw, float yx, float yy, float yz, float yw, float zx, float zy, float zz, float zw, float wx, float wy, float wz, float ww) {
//	matrix[0] = {xx,xy,xz,xw};
//	matrix[1] = { yx,yy,yz,yw };
//	matrix[2] = { zx,zy,zz,zw };
//	matrix[3] = { wx,wy,wz,ww };
//}
//
//Matrix Matrix::ToMatrix(Transform transform) {
//	glm::vec3 right = { 1.0f, 0.0f, 0.0f };
//	glm::vec3 up = { 0.0f, 1.0f, 0.0f};
//	glm::vec3 forward = { 0.0f, 0.0f, 1.0f };
//	
//	glm::vec3 Q = { transform.rotation.x,transform.rotation.x ,transform.rotation.x };
//	float32 scalar = transform.rotation.w;
//	glm::vec3 x = 2.0f * glm::dot(right, Q) * Q + (scalar * scalar - dot(Q, Q)) * right + 2.0f * scalar * cross(Q, right);
//	glm::vec3 y = 2.0f * dot(up, Q) * Q + (scalar * scalar - dot(Q, Q)) * up + 2.0f * scalar * cross(Q, up);
//	glm::vec3 z = 2.0f * dot(forward, Q) * Q + (scalar * scalar - dot(Q, Q)) * forward + 2.0f * scalar * cross(Q, forward);
//	x = x * transform.scale[0];
//	y = y * transform.scale[1];
//	z = z * transform.scale[2];
//
//	glm::vec3 t = {transform.position[0],transform.position[1] ,transform.position[2] };
//
//	return Matrix(
//		x.x, x.y, x.z, 0,
//		y.x, y.y, y.z, 0,
//		z.x, z.y, z.z, 0,
//		t.x, t.y, t.z, 1
//	);
//}