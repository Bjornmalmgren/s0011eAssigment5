#include "config.h"
#include "AiMovement.h"
#include "core/transform.h"
#include "render/physics.h"
#include "render/debugrender.h"
#include "render/RayCastComponent.h"
#include "imgui.h"
using namespace glm;
void AiMovement::Update(double dt) {
    if (slowing == 1 || nearNode == 1)
    {
        if (currentSpeed <= 0) {
            currentSpeed = 0;
        }
    }
    else
    {
         this->currentSpeed = mix(this->currentSpeed, this->normalSpeed, std::min(1.0f, (float)dt * 30.0f));

    }
    if (currentSpeed > 0.008) {
        currentSpeed = 0.008;
    }
    
    std::vector<RayCastComponent*> avoidanceRays;
    std::vector<RayCastComponent*> slowingRays;

    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 0));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 1));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 2));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 3));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 8));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 9));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 10));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 11));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 12));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 13));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 14));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 15));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 16));

    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 4));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 5));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 6));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 7));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 12));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 13));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 14));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 15));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 16));
    if (slowingRays[0]->raycast.hit == true || slowingRays[1]->raycast.hit == true || slowingRays[2]->raycast.hit == true || slowingRays[3]->raycast.hit == true|| slowingRays[4]->raycast.hit == true || slowingRays[5]->raycast.hit == true || slowingRays[6]->raycast.hit == true || slowingRays[7]->raycast.hit == true || slowingRays[8]->raycast.hit == true) {
        if (currentSpeed > 0.003) {
            this->currentSpeed -= 0.005;
        }
        

        slowing = 1;
    }
    else
    {
        slowing = 0;
    }
   


    glm::vec3 desiredVelocity = glm::vec3(0, 0, currentSpeed);
    desiredVelocity = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(desiredVelocity, 0.0f);
    
    linearVelocity = glm::mix(linearVelocity, desiredVelocity, (double)(dt * accelerationFactor));
    linearVelocitys = linearVelocity*(float)(dt + 10.0f);
   ((Transform*)owner->FindComponent(TRANSFORM))->position += linearVelocity* (float)(dt + 10.0f);
    
    


    vec3 targetdir = nextNode->position - ((Transform*)owner->FindComponent(TRANSFORM))->position;
    targetdir = normalize(targetdir);
    vec3 up = ((Transform*)owner->FindComponent(TRANSFORM))->transform[1];
    vec3 right = ((Transform*)owner->FindComponent(TRANSFORM))->transform[0];
    vec3 forward = ((Transform*)owner->FindComponent(TRANSFORM))->transform[2];

    float newRoll = dot(targetdir, -right);
    float newPitch = dot(targetdir, -up);
    float newYaw = dot(targetdir, right);

    if (avoidanceRays[8]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3( 1 * dt,0, 0));
    }
    else if (avoidanceRays[9]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(1 * dt, 0, 0));
    }
    else if (avoidanceRays[10]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(-1 * dt, 0, 0));
    }
    if (avoidanceRays[11]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, -1 * dt, 0));
    }
    else if (avoidanceRays[12]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, 1 * dt, 0));
    }


    if (avoidanceRays[0]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(1*dt, 0, 0));
    }
    else if (avoidanceRays[1]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(-1 * dt, 0, 0));
    }
    else
    {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(newPitch * dt, newYaw * dt, newRoll * dt));
    }

    if (avoidanceRays[2]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, -1 * dt, 0));
    }
    else if (avoidanceRays[3]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, 1 * dt, 0));
    }
    else
    {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(newPitch * dt, newYaw * dt, newRoll * dt));
    }

    if (avoidanceRays[4]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, 0, -1 * dt));
    }
    else if (avoidanceRays[5]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, 0, 1 * dt));
    }
    else if (avoidanceRays[6]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, 0, -1 * dt));
    }
    else if (avoidanceRays[7]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, 0, 1 * dt));
    }
    else
    {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(newPitch * dt, newYaw * dt, newRoll * dt));
    }

   
    
    glm::mat4 T = glm::translate(((Transform*)owner->FindComponent(TRANSFORM))->position) * (glm::mat4)((Transform*)owner->FindComponent(TRANSFORM))->rotation;
    ((Transform*)owner->FindComponent(TRANSFORM))->transform = T;
    // + ((Transform*)owner->FindComponent(TRANSFORM))->position
    Debug::DrawLine(((Transform*)owner->FindComponent(TRANSFORM))->position, targetdir + ((Transform*)owner->FindComponent(TRANSFORM))->position, 1, vec4(1, 1, 0, 1), vec4(1, 1, 0, 1),Debug::RenderMode::AlwaysOnTop);


    if (glm::distance(((Transform*)owner->FindComponent(TRANSFORM))->position, nextNode->position) <=12 || glm::distance(((Transform*)owner->FindComponent(TRANSFORM))->position, previousNode->position) <= 5) {
        if (this->currentSpeed <= 0.005) {

        }
        else
        {
            this->currentSpeed -= 0.005;
        }
        nearNode = 1;
    }
    else
    {
        nearNode = 0;
    }
    if (CheckPosition(((Transform*)owner->FindComponent(TRANSFORM))->position)) {
        previousNode = nextNode;
        AssignNextNode(nextNode->neighBours[0]);
        
    }
}

bool AiMovement::CheckPosition(glm::vec3 shipPos) {
    
   
    if (glm::distance(shipPos, nextNode->position) <= 4) {
        return true;
    }
    return false;
}

void AiMovement::LookAt() {
    vec3 targetdir = nextNode->position - ((Transform*)owner->FindComponent(TRANSFORM))->position;
    targetdir = normalize(targetdir);
    vec3 up = ((Transform*)owner->FindComponent(TRANSFORM))->transform[1];
    vec3 right = ((Transform*)owner->FindComponent(TRANSFORM))->transform[0];
    vec3 forward = ((Transform*)owner->FindComponent(TRANSFORM))->transform[2];

    float newRoll = dot(targetdir, right);
    float newPitch = dot(targetdir, up);
    float newYaw = dot(targetdir, -right);
    ((Transform*)owner->FindComponent(TRANSFORM))->rotation = quat(vec3(newPitch, newYaw, newRoll)) * ((Transform*)owner->FindComponent(TRANSFORM))->rotation;
}

void AiMovement::Start() {
    type = AIMOVEMENT; 
}

void AiMovement::AssignNextNode(Node* node) {
    nextNode = node;
    


}