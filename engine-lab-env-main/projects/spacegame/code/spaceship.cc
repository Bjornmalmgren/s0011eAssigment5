#include "config.h"
#include "spaceship.h"
#include "render/input/inputserver.h"
#include "render/cameramanager.h"
#include "render/physics.h"
#include "render/debugrender.h"
#include "render/particlesystem.h"
#include "render/ParticleComponent.h"
#include "core/InputComponent.h"
using namespace Input;
using namespace glm;
using namespace Render;

namespace Game
{

SpaceShip::SpaceShip()
{
    
}

void
SpaceShip::Start() {
   
    uint32_t numParticles = 2048;
   /* ((ParticleComponent*)FindComponent(PARTICLEEMITTER, 0))->emiter = new ParticleEmitter(numParticles);
    ((ParticleComponent*)FindComponent(PARTICLEEMITTER, 0))->emiter->data = {
        .origin = glm::vec4(((Transform*)FindComponent(TRANSFORM))->position + (vec3(((Transform*)FindComponent(TRANSFORM))->transform[2]) * emitterOffset),1),
        .dir = glm::vec4(glm::vec3(-((Transform*)FindComponent(TRANSFORM))->transform[2]), 0),
        .startColor = glm::vec4(0.38f, 0.76f, 0.95f, 1.0f) * 2.0f,
        .endColor = glm::vec4(0,0,0,1.0f),
        .numParticles = numParticles,
        .theta = glm::radians(0.0f),
        .startSpeed = 1.2f,
        .endSpeed = 0.0f,
        .startScale = 0.025f,
        .endScale = 0.0f,
        .decayTime = 2.58f,
        .randomTimeOffsetDist = 2.58f,
        .looping = 1,
        .emitterType = 1,
        .discRadius = 0.020f
    };
    ((ParticleComponent*)FindComponent(PARTICLEEMITTER, 1))->emiter = new ParticleEmitter(numParticles);
    ((ParticleComponent*)FindComponent(PARTICLEEMITTER, 1))->emiter->data = ((ParticleComponent*)FindComponent(PARTICLEEMITTER, 0))->emiter->data;

    ParticleSystem::Instance()->AddEmitter(((ParticleComponent*)FindComponent(PARTICLEEMITTER, 0))->emiter);
    ParticleSystem::Instance()->AddEmitter(((ParticleComponent*)FindComponent(PARTICLEEMITTER, 1))->emiter);*/
}
void
SpaceShip::Update(float dt)
{
 /*   Mouse* mouse = Input::GetDefaultMouse();
    Keyboard* kbd = Input::GetDefaultKeyboard();*/

    /*Camera* cam = CameraManager::GetCamera(CAMERA_MAIN);*/

   /* if (kbd->held[Key::W])
    {
        if (kbd->held[Key::Shift])
            this->currentSpeed = mix(this->currentSpeed, this->boostSpeed, std::min(1.0f, dt * 30.0f));
        else
            this->currentSpeed = mix(this->currentSpeed, this->normalSpeed, std::min(1.0f, dt * 90.0f));
    }
    else
    {
        this->currentSpeed = 0;
    }
    vec3 desiredVelocity = vec3(0, 0, this->currentSpeed);
    desiredVelocity = ((Transform*)FindComponent(TRANSFORM))->transform * vec4(desiredVelocity, 0.0f);

    this->linearVelocity = mix(this->linearVelocity, desiredVelocity, dt * accelerationFactor);

    float rotX = kbd->held[Key::Left] ? 1.0f : kbd->held[Key::Right] ? -1.0f : 0.0f;
    float rotY = kbd->held[Key::Up] ? -1.0f : kbd->held[Key::Down] ? 1.0f : 0.0f;
    float rotZ = kbd->held[Key::A] ? -1.0f : kbd->held[Key::D] ? 1.0f : 0.0f;*/

 /*   ((Transform*)FindComponent(TRANSFORM))->position += ((InputComponent*)FindComponent(INPUT))->linearVelocity * dt * 10.0f;

    const float rotationSpeed = 1.8f * dt;
    rotXSmooth = mix(rotXSmooth, ((InputComponent*)FindComponent(INPUT))->rotX * rotationSpeed, dt * cameraSmoothFactor);
    rotYSmooth = mix(rotYSmooth, ((InputComponent*)FindComponent(INPUT))->rotY * rotationSpeed, dt * cameraSmoothFactor);
    rotZSmooth = mix(rotZSmooth, ((InputComponent*)FindComponent(INPUT))->rotZ * rotationSpeed, dt * cameraSmoothFactor);
    quat localOrientation = quat(vec3(-rotYSmooth, rotXSmooth, rotZSmooth));
    ((Transform*)FindComponent(TRANSFORM))->rotation = ((Transform*)FindComponent(TRANSFORM))->rotation * localOrientation;
    this->rotationZ -= rotXSmooth;
    this->rotationZ = clamp(this->rotationZ, -45.0f, 45.0f);
    mat4 T = translate(((Transform*)FindComponent(TRANSFORM))->position) * (mat4)((Transform*)FindComponent(TRANSFORM))->rotation;
    ((Transform*)FindComponent(TRANSFORM))->transform = T * (mat4)quat(vec3(0, 0, rotationZ));
    this->rotationZ = mix(this->rotationZ, 0.0f, dt * cameraSmoothFactor);*/

    // update camera view transform
   /* vec3 desiredCamPos = ((Transform*)FindComponent(TRANSFORM))->position + vec3(((Transform*)FindComponent(TRANSFORM))->transform * vec4(0, camOffsetY, -4.0f, 0));
    this->camPos = mix(this->camPos, desiredCamPos, dt * cameraSmoothFactor);
    cam->view = lookAt(this->camPos, this->camPos + vec3(((Transform*)FindComponent(TRANSFORM))->transform[2]), vec3(((Transform*)FindComponent(TRANSFORM))->transform[1]));*/

    //this->particleEmitter->data.decayTime = 0.16f;//+ (0.01f  * t);
    //this->particleEmitter->data.randomTimeOffsetDist = 0.06f;/// +(0.01f * t);
}



}