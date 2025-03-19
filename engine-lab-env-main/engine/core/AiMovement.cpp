#include "config.h"
#include "AiMovement.h"
#include "core/transform.h"
#include "render/physics.h"
#include "render/debugrender.h"
#include "render/RayCastComponent.h"
#include "imgui.h"
#include "core/StarShipManager.h"
#include "core/transform.h"
#include "core/Allocators.h"
using namespace glm;
void AiMovement::Update(double dt) {
    sec++;
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
    if (currentSpeed > 0.007) {
        currentSpeed = 0.007;
    }
    
    std::vector<RayCastComponent*> avoidanceRays;
    std::vector<RayCastComponent*> slowingRays;
    RayCastComponent* playerDetection = ((RayCastComponent*)owner->FindComponent(RAYCAST, 25));
    RayCastComponent* guns = ((RayCastComponent*)owner->FindComponent(RAYCAST, 26));

    if (sec >= 320 && playerDetection->raycast.hit) {
        for (int i = 0; i < allo->collisionAllocator.allocatedSpace.size(); i++)
        {
            if (playerDetection->raycast.collider.index == allo->collisionAllocator.allocatedSpace[i]->colliderID.index) {
                if (allo->collisionAllocator.allocatedSpace[i]->owner != NULL) {

                    if (allo->collisionAllocator.allocatedSpace[i]->owner->spaceshipType != NONE) {
                        guns->sendCast = true;
                        guns->dir = glm::vec3(((Component::Transform*)owner->FindComponent(TRANSFORM))->transform[2]);
                       
                        glm::vec3 lw = glm::vec3(0.391073, -0.130853, 1.28339);  // left weapon
                        glm::vec3 rw = glm::vec3(-0.391073, -0.130853, 1.28339);  // left weapon
                        glm::vec3 poss = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(lw), 0.0f);


                        glm::vec3 poss2 = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(rw), 0.0f);

                        glm::vec3 pos = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss;
                        glm::vec3 pos2 = ((Transform*)owner->FindComponent(TRANSFORM))->position + poss2;


                        Render::ParticleEmitter* rightWeapon = new Render::ParticleEmitter(2048);
                        Render::ParticleEmitter* leftWeapon = new Render::ParticleEmitter(2048);
                        float projectileSpeed = 100;
                            //leftWeapom = new Render::ParticleEmitter(2048);
                            leftWeapon->data = {
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
                            Render::ParticleSystem::Instance()->AddEmitter(leftWeapon);

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
                            Render::ParticleSystem::Instance()->AddEmitter(rightWeapon);
                        break;
                    }
                }






            }
        }

        
    }

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
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 17));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 18));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 19));
    avoidanceRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 20));

    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 4));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 5));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 6));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 7));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 12));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 13));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 14));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 15));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 16));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 21));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 22));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 23));
    slowingRays.push_back((RayCastComponent*)owner->FindComponent(RAYCAST, 24));

    slowing = 0;
    for (int i = 0; i < slowingRays.size(); i++)
    {
        if (slowingRays[i]->raycast.hit == true) {
            if (currentSpeed > 0.002) {
                this->currentSpeed -= 0.0009;
            }


            slowing = 1;
            break;
        }
    }

   


    glm::vec3 desiredVelocity = glm::vec3(0, 0, currentSpeed);
    desiredVelocity = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(desiredVelocity, 0.0f);
    
    linearVelocity = glm::mix(linearVelocity, desiredVelocity, (double)(dt * accelerationFactor));
    linearVelocitys = linearVelocity*(float)(dt + 10.0f);
   ((Transform*)owner->FindComponent(TRANSFORM))->position += linearVelocity* (float)(dt + 10.0f);
    
    


    vec3 targetdir = nextNode->position - ((Transform*)owner->FindComponent(TRANSFORM))->position;
    if (aiType == NEUTRAL && startshipManager->player != NULL) {
        if (startshipManager->player->Destroyed == true) {

        }
        else if (glm::distance(((Transform*)owner->FindComponent(TRANSFORM))->position, ((Transform*)startshipManager->player->FindComponent(TRANSFORM))->position) <= 30) {
            targetdir = ((Transform*)startshipManager->player->FindComponent(TRANSFORM))->position - ((Transform*)owner->FindComponent(TRANSFORM))->position;
        }
    }
    if (aiType == DEFENSIVE && startshipManager->player != NULL) {

        if (startshipManager->player->Destroyed == true) {

        }
        else if (glm::distance(((Transform*)owner->FindComponent(TRANSFORM))->position, ((Transform*)startshipManager->player->FindComponent(TRANSFORM))->position) <= 40) {
            targetdir = ((Transform*)startshipManager->player->FindComponent(TRANSFORM))->position - ((Transform*)owner->FindComponent(TRANSFORM))->position;
            targetdir *= -1;
        }
    }
    if (aiType == AGGRESIVE && startshipManager->player != NULL) {
        if (startshipManager->player->Destroyed == true) {

        }
        else if (glm::distance(((Transform*)owner->FindComponent(TRANSFORM))->position, ((Transform*)startshipManager->player->FindComponent(TRANSFORM))->position) <= 60) {
            targetdir = ((Transform*)startshipManager->player->FindComponent(TRANSFORM))->position - ((Transform*)owner->FindComponent(TRANSFORM))->position;
        }
    }
    targetdir = normalize(targetdir);
    vec3 up = ((Transform*)owner->FindComponent(TRANSFORM))->transform[1];
    vec3 right = ((Transform*)owner->FindComponent(TRANSFORM))->transform[0];
    vec3 forward = ((Transform*)owner->FindComponent(TRANSFORM))->transform[2];

    float newRoll = dot(targetdir, -right);
    float newPitch = dot(targetdir, -up);
    float newYaw = dot(targetdir, right);

    if (avoidanceRays[13]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(-1 * dt, 0, 0));
    }
    else if (avoidanceRays[14]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(-1 * dt, 0, 0));
    }
    else if (avoidanceRays[15]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(1 * dt, 0, 0));
    }
    if (avoidanceRays[16]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(1 * dt, 0, 0));
    }
    
    /*if (avoidanceRays[8]->raycast.hit) {
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
    else
    {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(newPitch * dt, newYaw * dt, newRoll * dt));
    }*/

    
    

    if (avoidanceRays[0]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(1*dt, 0, 0));
    }
    else if (avoidanceRays[1]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(-1 * dt, 0, 0));
    } 
    else if(avoidanceRays[8]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(1 * dt, 0, 0));
    }
    else if (avoidanceRays[9]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(1 * dt, 0, 0));
    }
    else if (avoidanceRays[10]->raycast.hit) {
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
    else if (avoidanceRays[11]->raycast.hit) {
        ((Transform*)owner->FindComponent(TRANSFORM))->rotation = ((Transform*)owner->FindComponent(TRANSFORM))->rotation * quat(vec3(0, -1 * dt, 0));
    }
    else if (avoidanceRays[12]->raycast.hit) {
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
   

   
    
    glm::mat4 T = glm::translate(((Transform*)owner->FindComponent(TRANSFORM))->position) * (glm::mat4)((Transform*)owner->FindComponent(TRANSFORM))->rotation;
    ((Transform*)owner->FindComponent(TRANSFORM))->transform = T;
    // + ((Transform*)owner->FindComponent(TRANSFORM))->position
    Debug::DrawLine(((Transform*)owner->FindComponent(TRANSFORM))->position, targetdir + ((Transform*)owner->FindComponent(TRANSFORM))->position, 1, vec4(1, 1, 0, 1), vec4(1, 1, 0, 1),Debug::RenderMode::AlwaysOnTop);


    if (glm::distance(((Transform*)owner->FindComponent(TRANSFORM))->position, nextNode->position) <=18 || glm::distance(((Transform*)owner->FindComponent(TRANSFORM))->position, previousNode->position) <= 7) {
        if (this->currentSpeed <= 0.002) {

        }
        else
        {
            this->currentSpeed -= 0.0005;
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
    int dist = 1000000;
    int index = 0;
    for (int i = 0; i < nodeMGR->nodes.size(); i++)
    {
        int d = glm::distance(((Transform*)owner->FindComponent(TRANSFORM))->position, nodeMGR->nodes[i]->position);
        if (d < dist) {
            dist = d;
            index = i;
        }
    }
    nearestNode = index;
}

bool AiMovement::CheckPosition(glm::vec3 shipPos) {
    
   
    if (glm::distance(shipPos, nextNode->position) <= 8) {
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