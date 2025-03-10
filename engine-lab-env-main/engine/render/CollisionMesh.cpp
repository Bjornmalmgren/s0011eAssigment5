#include "config.h"
#include "CollisionMesh.h"
#include "core/transform.h"
#include "render/debugrender.h"
void Component::CollisionMesh::Update(double dt) {
    if (collisionCheck == true) {
        CheckCollisions();
    }
}

uint32_t Component::CollisionMesh::id() {
	return 0;
}
bool Component::CollisionMesh::CheckCollisions()
{
    glm::mat4 rotation = (glm::mat4)((Transform*)owner->FindComponent(TRANSFORM))->rotation;
    bool hit = false;
    for (int i = 0; i < sizeof(colliderEndPoints) / sizeof(glm::vec3); i++)
    {
        glm::vec3 pos = ((Transform*)owner->FindComponent(TRANSFORM))->position;
        glm::vec3 dir = ((Transform*)owner->FindComponent(TRANSFORM))->transform * glm::vec4(glm::normalize(colliderEndPoints[i]), 0.0f);
        float len = glm::length(colliderEndPoints[i]);
        Physics::RaycastPayload payload = Physics::Raycast(((Transform*)owner->FindComponent(TRANSFORM))->position, dir, len);

        // debug draw collision rays
        Debug::DrawLine(pos, pos + dir * len, 1.0f, glm::vec4(0, 1, 0, 1), glm::vec4(0, 1, 0, 1), Debug::RenderMode::AlwaysOnTop);

        if (payload.hit)
        {
            Debug::DrawDebugText("HIT", payload.hitPoint, glm::vec4(1, 1, 1, 1));
            hit = true;
            owner->Deallocate();
            return hit;
        }
    }
    return hit;
}
Component::CollisionMesh::~CollisionMesh() {

}