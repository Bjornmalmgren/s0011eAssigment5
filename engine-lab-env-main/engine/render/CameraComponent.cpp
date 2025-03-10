#include "config.h"
#include "CameraComponent.h"
#include "core/transform.h"
void CameraComponent::Update(double dt) {
    glm::vec3 desiredCamPos = ((Transform*)owner->FindComponent(TRANSFORM))->position + glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(0, camOffsetY, -4.0f, 0));
    this->camPos = mix(this->camPos, desiredCamPos, dt * cameraSmoothFactor);
    cam->view = glm::lookAt(this->camPos, this->camPos + glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform[2]), glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform[1]));
}