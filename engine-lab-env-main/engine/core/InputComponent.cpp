#include "config.h"
#include "InputComponent.h"
#include "core/transform.h"
#include "render/physics.h"
using namespace Input;
using namespace glm;
void InputComponent::Update(double dt) {
    Mouse* mouse = Input::GetDefaultMouse();
    Keyboard* kbd = Input::GetDefaultKeyboard();
 

    if (kbd->held[Key::W])
    {
        if (kbd->held[Key::Shift])
            this->currentSpeed = mix(this->currentSpeed, this->boostSpeed, std::min(1.0f, (float)dt * 30.0f));
        else
            this->currentSpeed = mix(this->currentSpeed, this->normalSpeed, std::min(1.0f, (float)dt * 90.0f));
        
    }
    else
    {
        this->currentSpeed = 0;
    }
    vec3 desiredVelocity = vec3(0, 0, this->currentSpeed);
    desiredVelocity = ((Transform*)owner->FindComponent(TRANSFORM))->transform * vec4(desiredVelocity, 0.0f);

    this->linearVelocity = glm::mix(this->linearVelocity, desiredVelocity, dt * accelerationFactor);

    rotX = kbd->held[Key::Left] ? 1.0f : kbd->held[Key::Right] ? -1.0f : 0.0f;
    rotY = kbd->held[Key::Up] ? -1.0f : kbd->held[Key::Down] ? 1.0f : 0.0f;
    rotZ = kbd->held[Key::A] ? -1.0f : kbd->held[Key::D] ? 1.0f : 0.0f;
}