#include "config.h"
#include "CameraComponent.h"
#include "core/transform.h"
#include "render/input/inputserver.h"
using namespace Input;
void CameraComponent::Update(double dt) {
    glm::vec3 desiredCamPos = ((Transform*)owner->FindComponent(TRANSFORM))->position + glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(camOffsetX, camOffsetY, camOffsetZ, 0));
    this->camPos = mix(this->camPos, desiredCamPos, dt * cameraSmoothFactor);
    cam->view = glm::lookAt(this->camPos, this->camPos + glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform[2]), glm::vec3(((Transform*)owner->FindComponent(TRANSFORM))->transform[1]));
   Input::Keyboard* kbd = Input::GetDefaultKeyboard();
   if (kbd->pressed[Input::Key::Control]) {
       moveCamera = !moveCamera;
   }
   if (moveCamera == true) {
       camOffsetX = kbd->held[Key::Left] ? 10.0f : kbd->held[Key::Right] ? -10.0f : 0.0f;
    
       camOffsetZ = kbd->held[Key::A] ? -10.0f : kbd->held[Key::D] ? 10.0f : 0.0f;
   }
}