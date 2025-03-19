#pragma once
#include "Allocator.h"
#include "render/CollisionMesh.h"
#include "render/Renderable.h"
#include "core/transform.h"
#include "render/ContinuesMovement.h"
#include "render/ParticleComponent.h"
#include "core/InputComponent.h"
#include "render/CameraComponent.h"
#include "render/RayCastComponent.h"
#include "core/AiMovement.h"
#include "Allocator.h"
class Allocators
{
public:
	Allocators(){}
	Allocator<Component::Renderable, 1024> renderableAllocator;
	Allocator<Component::Transform, 1024> transformAllocator;
	Allocator<Component::CollisionMesh, 1024> collisionAllocator;
	Allocator<Component::ContinuesMovement, 1024> cmovementAllocator;
	Allocator<Component::ParticleComponent, 1024> particleAllocator;
	Allocator<Component::RayCastComponent, 500> raycastAllocator;
	Allocator<Component::AiMovement, 100> aiAllocator;
	Allocator<Component::InputComponent, 1> inputAllocator;
	Allocator<Component::CameraComponent, 5> cameraAllocator;
	Allocator<Entity, 1024> entityAllocator;
	static Allocators* instance();
};
#define allo Allocators::instance()

