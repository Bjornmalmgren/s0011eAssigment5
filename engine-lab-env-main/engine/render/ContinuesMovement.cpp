#include "config.h"
#include "ContinuesMovement.h"
#include "core/transform.h"
#include "core/InputComponent.h"
#include "render/CameraComponent.h"
#include <random>
void Component::ContinuesMovement::Update(double dt) {
	if (rotX > 0 || rotY > 0 || rotZ > 0) {
		srand(time(0));
		int random = rand() % 1001;
		random +=500;
		float rotationSpeed = 1.3 * dt;
		glm::mat4 transform = ((Transform*)owner->FindComponent(TRANSFORM))->transform;
		glm::vec3 v = glm::vec3(0, 0, 0);
		if (rotationDir == 1) {
			v = glm::vec3(1, 0, 0);
		}else if(rotationDir == 2) {
			v = glm::vec3(0, 1, 0);
		}
		else if (rotationDir == 3) {
			v = glm::vec3(0, 0, 1);
		}
		
		glm::mat4 m = glm::rotate_slow(transform, rotZ/random, v);
		((Transform*)owner->FindComponent(TRANSFORM))->transform = m;
		
		/*glm::quat lRotation = glm::quat(glm::vec3(-rotYSmooth, rotXSmooth, rotZSmooth));
		rotation *= lRotation;
		rotationZ -= rotXSmooth;
		rotationZ = glm::clamp(rotationZ, -45.0f, 45.0f);
		glm::vec3 pos = glm::vec3(transform[0][0], transform[0][1], transform[0][2]);
		glm::mat4 T = glm::translate(pos) * (glm::mat4)rotation;
		transform = T * (glm::mat4)glm::quat(glm::vec3(0, 0, rotationZ));
		rotationZ = glm::mix(rotationZ, 0.0f, dt * 10);
		transform[3] = glm::vec4(pos, 1);
		((Transform*)owner->FindComponent(TRANSFORM))->transform = transform;*/
	}
	if (move == true) {
		Movement(dt);
	}
}

void Component::ContinuesMovement::Start() {
	srand(time(0));
	int random = rand() % 3;
	random += 1;
	rotationDir = random;
	type = CONTINUESFORCE;
}

void ContinuesMovement::Movement(double dt) {
	((Transform*)owner->FindComponent(TRANSFORM))->position += ((InputComponent*)owner->FindComponent(INPUT))->linearVelocity * (float)(dt * 10.0f);

	const float rotationSpeed = 1.8f * dt;
	rotXSmooth = glm::mix(rotXSmooth, ((InputComponent*)owner->FindComponent(INPUT))->rotX * rotationSpeed, dt *  ((CameraComponent*)owner->FindComponent(CAMERA))->cameraSmoothFactor);
	rotYSmooth = glm::mix(rotYSmooth, ((InputComponent*)owner->FindComponent(INPUT))->rotY * rotationSpeed, dt * ((CameraComponent*)owner->FindComponent(CAMERA))->cameraSmoothFactor);
	rotZSmooth = glm::mix(rotZSmooth, ((InputComponent*)owner->FindComponent(INPUT))->rotZ * rotationSpeed, dt * ((CameraComponent*)owner->FindComponent(CAMERA))->cameraSmoothFactor);
	glm::quat localOrientation = glm::quat(glm::vec3(-rotYSmooth, rotXSmooth, rotZSmooth));
	((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * localOrientation;
	this->rotationZ -= rotXSmooth;
	this->rotationZ = clamp(this->rotationZ, -45.0f, 45.0f);
	glm::mat4 T = glm::translate(((Transform*)owner->FindComponent(TRANSFORM))->position) * (glm::mat4)((Transform*)owner->FindComponent(TRANSFORM))->rotation;
	((Transform*)owner->FindComponent(TRANSFORM))->transform = T * (glm::mat4)glm::quat(glm::vec3(0, 0, rotationZ));
	this->rotationZ = glm::mix(this->rotationZ, 0.0f, dt * ((CameraComponent*)owner->FindComponent(CAMERA))->cameraSmoothFactor);
}