#include "config.h"
#include "InputComponent.h"
#include "core/transform.h"
#include "render/physics.h"
#include "core/transform.h"
#include "render/debugrender.h"
#include "render/RayCastComponent.h"
using namespace Input;
using namespace glm;
void InputComponent::Update(double dt) {
    Mouse* mouse = Input::GetDefaultMouse();
    Keyboard* kbd = Input::GetDefaultKeyboard();
    float projectileSpeed = 100;
    if (kbd->pressed[Key::Space]) {
        glm::vec3 lw =  glm::vec3(0.391073, -0.130853, 1.28339);  // left weapon
        glm::vec3 rw =  glm::vec3(-0.391073, -0.130853, 1.28339);  // left weapon
        glm::vec3 poss = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(lw), 0.0f);


        glm::vec3 poss2 = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(rw), 0.0f);

        glm::vec3 pos = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss;
        glm::vec3 pos2 = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss2;
       

        if (firstpress == true) {
            //leftWeapom = new Render::ParticleEmitter(2048);
            leftWeapom->data = {
            .origin = glm::vec4(pos,1),
            .dir = glm::vec4(glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]), 0),
            .startColor = glm::vec4(0, 1, 0, 1.0f),
            .endColor = glm::vec4(0,1,0,1.0f),
            .numParticles = 1024,
            .theta = glm::radians(0.0f),
            .startSpeed = projectileSpeed,
            .endSpeed = projectileSpeed,
            .startScale = 0.01,
            .endScale = 0.01,
            .decayTime = 1,
            .randomTimeOffsetDist = 0.001,
            .looping = 1,
            .emitterType = 1,
            .discRadius = 0.1f
            };
            Render::ParticleSystem::Instance()->AddEmitter(leftWeapom);

            rightWeapon->data = {
            .origin = glm::vec4(pos2,1),
            .dir = glm::vec4(glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]), 0),
            .startColor = glm::vec4(0, 1, 0, 1.0f),
            .endColor = glm::vec4(0,1,0,1.0f),
            .numParticles = 1024,
            .theta = glm::radians(0.0f),
            .startSpeed = projectileSpeed,
            .endSpeed = projectileSpeed,
            .startScale = 0.01,
            .endScale = 0.01,
            .decayTime = 1,
            .randomTimeOffsetDist = 0.001,
            .looping = 1,
            .emitterType = 1,
            .discRadius = 0.1f
            };
            Render::ParticleSystem::Instance()->AddEmitter(rightWeapon);
            ((Component::RayCastComponent*)owner->FindComponent(RAYCAST,0))->sendCast = true;
            ((Component::RayCastComponent*)owner->FindComponent(RAYCAST, 0))->dir = glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]);
            firstpress = false;
        }
        else
        {
            leftWeapom->data = {
            .origin = glm::vec4(pos,1),
            .dir = glm::vec4(glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]), 0),
            .startColor = glm::vec4(0, 1, 0, 1.0f),
            .endColor = glm::vec4(0,1,0,1.0f),
            .numParticles = 1024,
            .theta = glm::radians(0.0f),
            .startSpeed = projectileSpeed,
            .endSpeed = projectileSpeed,
            .startScale = 0.01,
            .endScale = 0.01,
            .decayTime = 1,
            .randomTimeOffsetDist = 0.001,
            .looping = 1,
            .emitterType = 1,
            .discRadius = 0.1f
            };
            Render::ParticleSystem::Instance()->AddEmitter(leftWeapom);
            rightWeapon->data = {
            .origin = glm::vec4(pos2,1),
            .dir = glm::vec4(glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]), 0),
            .startColor = glm::vec4(0, 1, 0, 1.0f),
            .endColor = glm::vec4(0,1,0,1.0f),
            .numParticles = 1024,
            .theta = glm::radians(0.0f),
            .startSpeed = projectileSpeed,
            .endSpeed = projectileSpeed,
            .startScale = 0.01,
            .endScale = 0.01,
            .decayTime = 1,
            .randomTimeOffsetDist = 0.001,
            .looping = 1,
            .emitterType = 1,
            .discRadius = 0.1f
            };
            Render::ParticleSystem::Instance()->AddEmitter(rightWeapon);
            ((Component::RayCastComponent*)owner->FindComponent(RAYCAST, 0))->sendCast = true;
            ((Component::RayCastComponent*)owner->FindComponent(RAYCAST, 0))->dir = glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]);
        }
        
    }
    else {
        glm::vec3 lw = glm::vec3(0.391073, -0.130853, 1.28339);  // left weapon
        glm::vec3 rw =glm::vec3(-0.391073, -0.130853, 1.28339);  // right weapon
        glm::vec3 poss = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(lw), 0.0f);

        glm::vec3 poss2 = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(rw), 0.0f);


        glm::vec3 pos = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss;
        glm::vec3 pos2 = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss2;

        vec3 dir = glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]);
        float length = 10;
        /*Physics::RaycastPayload leftWeaponRay = Physics::Raycast(pos, dir, length);
        Physics::RaycastPayload rightWeaponRay = Physics::Raycast(pos2, dir, length);
        Debug::DrawLine(pos, pos + dir* length, 1.0f, glm::vec4(0, 1, 0, 1), glm::vec4(0, 1, 0, 1), Debug::RenderMode::AlwaysOnTop);
        Debug::DrawLine(pos2, pos2 + dir* length, 1.0f, glm::vec4(0, 1, 0, 1), glm::vec4(0, 1, 0, 1), Debug::RenderMode::AlwaysOnTop);*/

        leftWeapom->data = {
            .origin = glm::vec4(pos,1),
            .dir = glm::vec4(glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]), 0),
            .startColor = glm::vec4(0, 1, 0, 1.0f),
            .endColor = glm::vec4(0,1,0,1.0f),
            .numParticles = 1024,
            .theta = glm::radians(0.0f),
            .startSpeed = projectileSpeed,
            .endSpeed = projectileSpeed,
            .startScale = 0.01,
            .endScale = 0.01,
            .decayTime = 1,
            .randomTimeOffsetDist = 0.001,
            .looping = 0,
            .emitterType = 1,
            .discRadius = 0.1f
        };
        rightWeapon->data = {
           .origin = glm::vec4(pos2,1),
           .dir = glm::vec4(glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]), 0),
           .startColor = glm::vec4(0, 1, 0, 1.0f),
           .endColor = glm::vec4(0,1,0,1.0f),
           .numParticles = 1024,
           .theta = glm::radians(0.0f),
           .startSpeed = projectileSpeed,
           .endSpeed = projectileSpeed,
           .startScale = 0.01,
           .endScale = 0.01,
           .decayTime = 1,
           .randomTimeOffsetDist = 0.001,
           .looping = 0,
           .emitterType = 1,
           .discRadius = 0.1f
        };
    }

   
        
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