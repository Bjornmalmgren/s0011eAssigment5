#include "config.h"
#include "World.h"
#include "core/transform.h"
#include "core/InputComponent.h"
#include "render/CameraComponent.h"
#include "render/CollisionMesh.h"
#include "render/ContinuesMovement.h"
#include "render/ParticleComponent.h"
#include "render/Renderable.h"
#include "render/particlesystem.h"
#include "core/AiManager.h"

World::World() {
	
	for (int i = 0; i <  allo->renderableAllocator.Size(); i++)
	{
		Renderable* render = new Renderable();
		allo->renderableAllocator.AddItem(render);
		componentID->CreateId(allo->renderableAllocator.allocatedSpace.back());
		
		
	}
	for (int i = 0; i < allo->transformAllocator.Size(); i++)
	{	
		Transform* transd = new Transform();
		allo->transformAllocator.AddItem(transd);
		componentID->CreateId(allo->transformAllocator.allocatedSpace.back());
	}

	for (int i = 0; i < allo->collisionAllocator.Size(); i++)
	{
		CollisionMesh* transd = new CollisionMesh();
		allo->collisionAllocator.AddItem(transd);
		componentID->CreateId(allo->collisionAllocator.allocatedSpace.back());
	}
	for (int i = 0; i < allo->cmovementAllocator.Size(); i++)
	{
		ContinuesMovement* cm = new ContinuesMovement();
		allo->cmovementAllocator.AddItem(cm);
		componentID->CreateId(allo->cmovementAllocator.allocatedSpace.back());
	}
	for (int i = 0; i < allo->particleAllocator.Size(); i++)
	{
		ParticleComponent* cm = new ParticleComponent();
		allo->particleAllocator.AddItem(cm);
		componentID->CreateId(allo->particleAllocator.allocatedSpace.back());
	}
	for (int i = 0; i < allo->inputAllocator.Size(); i++)
	{

		InputComponent* cm = new InputComponent();
		allo->inputAllocator.AddItem(cm);
		componentID->CreateId(allo->inputAllocator.allocatedSpace.back());

	}
	for (int i = 0; i < allo->cameraAllocator.Size(); i++)
	{

		CameraComponent* cm = new CameraComponent();
		allo->cameraAllocator.AddItem(cm);
		componentID->CreateId(allo->cameraAllocator.allocatedSpace.back());

	}
	for (int i = 0; i < allo->raycastAllocator.Size(); i++)
	{

		RayCastComponent* cm = new RayCastComponent();
		allo->raycastAllocator.AddItem(cm);
		componentID->CreateId(allo->raycastAllocator.allocatedSpace.back());

	}
	for (int i = 0; i < allo->aiAllocator.Size(); i++)
	{
		AiMovement* aim = new AiMovement();
		allo->aiAllocator.AddItem(aim);
		componentID->CreateId(allo->aiAllocator.allocatedSpace.back());


	}
}
void World::CreateEntity() {
	Entity* ent = new Entity();
	entityID->CreateId(ent);
	allo->entityAllocator.AddItem(ent);
	entitys.push_back(ent);
}
void World::AddEntity(Entity* ent) {
	entitys.push_back(ent);
}
Entity* World::FindEntity(int id) {
	if (entityID->IsValid(id)) {
		return entityID->FindEntity(id);
	}
	else
	{
		return nullptr;
	}
	
}
void World::UpdateEntitys(double dt) {
	if (respawnPlayer == true) {
		bool respawn = startshipManager->CountDown();
		if(respawn == true) {
			respawnPlayer = false;
			CreateSpaceShip();
			startshipManager->player = entitys.back();
		}
	}
	if (AIManager->respawnvector.size() > 0) {
		
		Respawn respawn = AIManager->Respawn();
		if (respawn.respawnBool == true) {
			
			CreateAISpaceShip(respawn.nearestNode, respawn.aiType,respawn.color);
			AIManager->ClearUpVector();
			
		}
	}
	for (auto ent : entitys)
	{
		ent->drawRaycasts = startshipManager->drawRays;
		if (ent->Destroyed == true) {
			if (ent->spaceshipType == PLAYER) {
				respawnPlayer = true;
				startshipManager->player = NULL;
				activeCameras--;
			}
			if (AIManager->respawnvector.size() > 0) {
				activeCameras--;
			}
			for (int i = 0; i < allo->entityAllocator.allocatedSpace.size(); i++)
			{
				if (allo->entityAllocator.allocatedSpace[i]->id == ent->id) {
					allo->entityAllocator.RemoveItem(i);
					entityID->RemoveId(ent->id);
					entitys.erase(entitys.begin() + i);
					
				}
			}
			
		}
		else
		{
			for (auto comp : ent->components)
			{
				
				comp->Update(dt);
				if (ent->Destroyed == true) {
					break;
				}
			}
		}
		
	}
}

void World::StartEntitys() {
	for (auto ent : entitys)
	{
		for (auto comp : ent->components)
		{
			comp->Start();
		}
	}
}

void World::CreateSpaceShip() {
	CreateEntity();
	entitys.back()->spaceshipType = PLAYER;
	Component::Transform* transf = (Transform*)FindEmptyComponent(TRANSFORM);
	transf->owner = entitys.back();
	transf->position = glm::vec3(0);
	transf->rotation = glm::identity<glm::quat>();
	transf->transform = glm::mat4(1);
	Component::Renderable* render = (Renderable*)FindEmptyComponent(RENDERABLE);
	render->owner = entitys.back();

	Component::ParticleComponent* particle1 = (ParticleComponent*)FindEmptyComponent(PARTICLEEMITTER);
	particle1->owner = entitys.back();
	particle1->emiter = new Render::ParticleEmitter(2048);
	particle1->emiter->data = {
		.origin = glm::vec4(transf->position + (glm::vec3(transf->transform[2]) * -0.5f),1),
		.dir = glm::vec4(glm::vec3(-transf->transform[2]), 0),
		.startColor = glm::vec4(0.38f, 0.76f, 0.95f, 1.0f) * 2.0f,
		.endColor = glm::vec4(0,0,0,1.0f),
		.numParticles = 2048,
		.theta = glm::radians(0.0f),
		.startSpeed = 1.2f,
		.endSpeed = 0.0f,
		.startScale = 0.025f,
		.endScale = 0.0f,
		.decayTime = 2.58f,
		.randomTimeOffsetDist = 2.58f,
		.looping = 1,
		.emitterType = 1,
		.discRadius = 0.1f
	};


	Component::ParticleComponent* particle2 = (ParticleComponent*)FindEmptyComponent(PARTICLEEMITTER);
	particle2->owner = entitys.back();
	particle2->emiter = new Render::ParticleEmitter(2048);
	particle2->emiter->data = particle1->emiter->data;

	Component::CameraComponent* camera = (CameraComponent*)FindEmptyComponent(CAMERA);
	camera->owner = entitys.back();
	activeCameras++;

	Render::ParticleSystem::Instance()->AddEmitter(particle1->emiter);
	Render::ParticleSystem::Instance()->AddEmitter(particle2->emiter);

	Component::InputComponent* input = (InputComponent*)FindEmptyComponent(INPUT);
	input->owner = entitys.back();

	Component::ContinuesMovement* cmm = (ContinuesMovement*)FindEmptyComponent(CONTINUESFORCE);
	cmm->owner = entitys.back();
	cmm->move = true;

	Component::CollisionMesh* cMesh = (CollisionMesh*)FindEmptyComponent(COLLISIONMESH);
	cMesh->owner = entitys.back();
	cMesh->collisionCheck = true;

	cMesh->colliderID = Physics::CreateCollider(Physics::LoadColliderMesh("assets/space/spaceship_physics.glb"),  transf->transform,0);

	

	cMesh->colliderEndPoints[0] = glm::vec3(1.40173, 0.0, -0.225342);  // left wing back
	cMesh->colliderEndPoints[1] = glm::vec3(1.33578, 0.0, 0.088893);  // left wing front
	cMesh->colliderEndPoints[2] = glm::vec3(0.227107, -0.200232, -0.588618);  // left back engine bottom
	cMesh->colliderEndPoints[3] = glm::vec3(0.227107, 0.228809, -0.588618);  // left back engine top
	cMesh->colliderEndPoints[4] = glm::vec3(0.391073, -0.130853, 1.28339);  // left weapon
	cMesh->colliderEndPoints[5] = glm::vec3(0.134787, 0.0, 1.68965),  // left front
	cMesh->colliderEndPoints[6] = glm::vec3(0.134787, 0.250728, 0.647422);  // left wind shield

	cMesh->colliderEndPoints[7] = glm::vec3(-1.40173, 0.0, -0.225342);  // right wing back
	cMesh->colliderEndPoints[8] = glm::vec3(-1.33578, 0.0, 0.088893);  // right wing front
	cMesh->colliderEndPoints[9] = glm::vec3(-0.227107, -0.200232, -0.588618);  // right back engine bottom
	cMesh->colliderEndPoints[10] = glm::vec3(-0.227107, 0.228809, -0.588618);  // right back engine top
	cMesh->colliderEndPoints[11] = glm::vec3(-0.391073, -0.130853, 1.28339); // right weapon
	cMesh->colliderEndPoints[12] = glm::vec3(-0.134787, 0.0, 1.68965);  // right front
	cMesh->colliderEndPoints[13] = glm::vec3(-0.134787, 0.250728, 0.647422);  // right wind shield

	cMesh->colliderEndPoints[14] = glm::vec3(0.0, 0.525049, -0.392836);  // top back
	cMesh->colliderEndPoints[15] = glm::vec3(0.0, 0.739624, 0.102582);  // top fin
	cMesh->colliderEndPoints[16] = glm::vec3(0.0, -0.244758, 0.284825);  // bottom

	Component::RayCastComponent* raycast = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast->owner = entitys.back();
	raycast->AddRayCast(transf->position, transf->transform[2], 50);// left weapon
	raycast->slowMovingRay = true;
	raycast->pos = glm::vec3(0.391073, -0.20853, 1.28339);

	render->modelId = Render::LoadModel("assets/space/spaceship.glb");

	entitys.back()->components.push_back(transf);
	entitys.back()->components.push_back(render);
	entitys.back()->components.push_back(particle1);
	entitys.back()->components.push_back(particle2);
	entitys.back()->components.push_back(input);
	entitys.back()->components.push_back(camera);
	entitys.back()->components.push_back(cmm);
	entitys.back()->components.push_back(cMesh);
	entitys.back()->components.push_back(raycast);

	player = entitys.back();
}

void World::CreateAISpaceShip(int node, MovementType mtype, glm::vec4 color) {
	CreateEntity();
	entitys.back()->spaceshipType = AI1;
	Component::Transform* transf = (Transform*)FindEmptyComponent(TRANSFORM);
	transf->owner = entitys.back();
	glm::vec3 v = nodeMGR->nodes[node]->position;
	transf->position = glm::vec3(v);
	transf->rotation = glm::identity<glm::quat>();
	transf->transform = glm::mat4(1);
	Component::Renderable* render = (Renderable*)FindEmptyComponent(RENDERABLE);
	render->owner = entitys.back();

	Component::ParticleComponent* particle1 = (ParticleComponent*)FindEmptyComponent(PARTICLEEMITTER);
	particle1->owner = entitys.back();
	particle1->emiter = new Render::ParticleEmitter(2048);
	particle1->emiter->data = {
		.origin = glm::vec4(transf->position + (glm::vec3(transf->transform[2]) * -0.5f),1),
		.dir = glm::vec4(glm::vec3(-transf->transform[2]), 0),
		.startColor = color * 2.0f,
		.endColor = glm::vec4(0,0,0,1.0f),
		.numParticles = 2048,
		.theta = glm::radians(0.0f),
		.startSpeed = 1.2f,
		.endSpeed = 0.0f,
		.startScale = 0.025f,
		.endScale = 0.0f,
		.decayTime = 2.58f,
		.randomTimeOffsetDist = 2.58f,
		.looping = 1,
		.emitterType = 1,
		.discRadius = 0.1f
	};


	Component::ParticleComponent* particle2 = (ParticleComponent*)FindEmptyComponent(PARTICLEEMITTER);
	particle2->owner = entitys.back();
	particle2->emiter = new Render::ParticleEmitter(2048);
	particle2->emiter->data = particle1->emiter->data;

	

	Component::CameraComponent* camera = (CameraComponent*)FindEmptyComponent(CAMERA);
	camera->owner = entitys.back();
	camera->cam = nullptr;
	activeCameras++;
	Render::ParticleSystem::Instance()->AddEmitter(particle1->emiter);
	Render::ParticleSystem::Instance()->AddEmitter(particle2->emiter);

	Component::CollisionMesh* cMesh = (CollisionMesh*)FindEmptyComponent(COLLISIONMESH);
	cMesh->owner = entitys.back();
	cMesh->collisionCheck = true;

	
	//raycasts to avoid obstacles
	Component::RayCastComponent* raycast = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast->owner = entitys.back();
	raycast->AddRayCast(transf->position,glm::vec3(0, 0.6, 2), 7);

	Component::RayCastComponent* raycast2 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast2->owner = entitys.back();
	raycast2->AddRayCast(transf->position, glm::vec3(0, -0.6, 2), 7);

	Component::RayCastComponent* raycast3 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast3->owner = entitys.back();
	raycast3->AddRayCast(transf->position, glm::vec3(0.6, 0, 2), 7);

	Component::RayCastComponent* raycast4 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast4->owner = entitys.back();
	raycast4->AddRayCast(transf->position, glm::vec3(-0.6, 0, 2), 7);


	//wing raycasts
	Component::RayCastComponent* raycast9 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast9->owner = entitys.back();
	raycast9->AddRayCast(transf->position + glm::vec3(1.33578, 0.0, 0.088893), glm::vec3(0, -0.1, 2), 7);
	raycast9->pos = transf->transform * glm::vec4(glm::normalize(glm::vec3(1.33578, 0.0, 0.088893)), 0.0f);

	Component::RayCastComponent* raycast10 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast10->owner = entitys.back();
	raycast10->AddRayCast(transf->position + glm::vec3(1.33578, 0.0, 0.088893), glm::vec3(0, 0.1, 2), 7);
	raycast10->pos = glm::vec3(1.33578, 0.0, 0.088893);

	Component::RayCastComponent* raycast11 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast11->owner = entitys.back();
	raycast11->AddRayCast(transf->position +glm::vec3(-1.33578, 0.0, 0.088893), glm::vec3(0, -0.1, 2), 7);
	raycast11->pos = glm::vec3(-1.33578, 0.0, 0.088893);

	Component::RayCastComponent* raycast12 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast12->owner = entitys.back();
	raycast12->AddRayCast(transf->position+glm::vec3(-1.33578, 0.0, 0.088893), glm::vec3(0, 0.1, 2), 7);
	raycast12->pos = glm::vec3(-1.33578, 0.0, 0.088893);

	//diagonal raycast to avoid obstacles
	Component::RayCastComponent* raycast18 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast18->owner = entitys.back();
	raycast18->AddRayCast(transf->position, glm::vec3(-0.4, 0.4, 2), 5);

	Component::RayCastComponent* raycast19 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast19->owner = entitys.back();
	raycast19->AddRayCast(transf->position, glm::vec3(0.4, 0.4, 2), 5);

	Component::RayCastComponent* raycast20 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast20->owner = entitys.back();
	raycast20->AddRayCast(transf->position, glm::vec3(-0.4, -0.4, 2), 5);

	Component::RayCastComponent* raycast21 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast21->owner = entitys.back();
	raycast21->AddRayCast(transf->position, glm::vec3(0.4, -0.4, 2), 5);

	//diagonal raycast to slow down
	Component::RayCastComponent* raycast22 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast22->owner = entitys.back();
	raycast22->AddRayCast(transf->position, glm::vec3(0.2, 0.2, 1), 13);

	Component::RayCastComponent* raycast23 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast23->owner = entitys.back();
	raycast23->AddRayCast(transf->position, glm::vec3(-0.2, 0.2, 1), 13);

	Component::RayCastComponent* raycast24 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast24->owner = entitys.back();
	raycast24->AddRayCast(transf->position, glm::vec3(0.2, -0.2, 1), 13);

	Component::RayCastComponent* raycast25 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast25->owner = entitys.back();
	raycast25->AddRayCast(transf->position, glm::vec3(-0.2, -0.2, 1), 13);

	//raycast to slow down the ship
	Component::RayCastComponent* raycast5 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast5->owner = entitys.back();
	raycast5->AddRayCast(transf->position, glm::vec3(0, 0.3, 1), 13);

	Component::RayCastComponent* raycast6 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast6->owner = entitys.back();
	raycast6->AddRayCast(transf->position, glm::vec3(0, -0.3, 1), 13);

	Component::RayCastComponent* raycast7 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast7->owner = entitys.back();
	raycast7->AddRayCast(transf->position, glm::vec3(0.3, 0, 1), 13);
	Component::RayCastComponent* raycast8 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast8->owner = entitys.back();
	raycast8->AddRayCast(transf->position, glm::vec3(-0.3, 0, 1), 13);

	//centra raycats for avoiding obstacles in front
	Component::RayCastComponent* raycast13 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast13->owner = entitys.back();
	raycast13->AddRayCast(transf->position, glm::vec3(0, 0, 1), 7);

	Component::RayCastComponent* raycast14 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast14->owner = entitys.back();
	raycast14->AddRayCast(transf->position, glm::vec3(0, 0.1, 1), 7);

	Component::RayCastComponent* raycast15 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast15->owner = entitys.back();
	raycast15->AddRayCast(transf->position, glm::vec3(0, -0.1, 1), 7);

	Component::RayCastComponent* raycast16 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast16->owner = entitys.back();
	raycast16->AddRayCast(transf->position, glm::vec3(-0.1, 0, 1), 7);

	Component::RayCastComponent* raycast17 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast17->owner = entitys.back();
	raycast17->AddRayCast(transf->position, glm::vec3(0.1, 0, 1), 7);

	Component::AiMovement* aim = (AiMovement*)FindEmptyComponent(AIMOVEMENT);
	aim->owner = entitys.back();
	aim->aiType = mtype;

	//shooting detection
	Component::RayCastComponent* raycast26 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast26->owner = entitys.back();
	raycast26->AddRayCast(transf->position, transf->transform[2], 50);// left weapon
	raycast26->pos = glm::vec3(0.391073, -0.20853, 1.28339);
	raycast26->mask = 0;
	//shooting
	Component::RayCastComponent* raycast27 = (RayCastComponent*)FindEmptyComponent(RAYCAST);
	raycast27->owner = entitys.back();
	raycast27->AddRayCast(transf->position, transf->transform[2], 50);// left weapon
	raycast27->slowMovingRay = true;
	raycast27->pos = glm::vec3(0.391073, -0.20853, 1.28339);

	cMesh->colliderID = Physics::CreateCollider(Physics::LoadColliderMesh("assets/space/spaceship_physics.glb"), transf->transform,4);
	cMesh->colliderEndPoints[0] = glm::vec3(1.40173, 0.0, -0.225342);  // left wing back
	cMesh->colliderEndPoints[1] = glm::vec3(1.33578, 0.0, 0.088893);  // left wing front
	cMesh->colliderEndPoints[2] = glm::vec3(0.227107, -0.200232, -0.588618);  // left back engine bottom
	cMesh->colliderEndPoints[3] = glm::vec3(0.227107, 0.228809, -0.588618);  // left back engine top
	cMesh->colliderEndPoints[4] = glm::vec3(0.391073, -0.130853, 1.28339);  // left weapon
	cMesh->colliderEndPoints[5] = glm::vec3(0.134787, 0.0, 1.68965),  // left front
	cMesh->colliderEndPoints[6] = glm::vec3(0.134787, 0.250728, 0.647422);  // left wind shield

	cMesh->colliderEndPoints[7] = glm::vec3(-1.40173, 0.0, -0.225342);  // right wing back
	cMesh->colliderEndPoints[8] = glm::vec3(-1.33578, 0.0, 0.088893);  // right wing front
	cMesh->colliderEndPoints[9] = glm::vec3(-0.227107, -0.200232, -0.588618);  // right back engine bottom
	cMesh->colliderEndPoints[10] = glm::vec3(-0.227107, 0.228809, -0.588618);  // right back engine top
	cMesh->colliderEndPoints[11] = glm::vec3(-0.391073, -0.130853, 1.28339); // right weapon
	cMesh->colliderEndPoints[12] = glm::vec3(-0.134787, 0.0, 1.68965);  // right front
	cMesh->colliderEndPoints[13] = glm::vec3(-0.134787, 0.250728, 0.647422);  // right wind shield

	cMesh->colliderEndPoints[14] = glm::vec3(0.0, 0.525049, -0.392836);  // top back
	cMesh->colliderEndPoints[15] = glm::vec3(0.0, 0.739624, 0.102582);  // top fin
	cMesh->colliderEndPoints[16] = glm::vec3(0.0, -0.244758, 0.284825);  // bottom




	render->modelId = Render::LoadModel("assets/space/spaceship.glb");

	entitys.back()->components.push_back(transf);
	entitys.back()->components.push_back(render);
	entitys.back()->components.push_back(particle1);
	entitys.back()->components.push_back(particle2);
	entitys.back()->components.push_back(camera);
	entitys.back()->components.push_back(cMesh);
	
	entitys.back()->components.push_back(raycast);
	entitys.back()->components.push_back(raycast2);
	entitys.back()->components.push_back(raycast3);
	entitys.back()->components.push_back(raycast4);
	entitys.back()->components.push_back(raycast5);
	entitys.back()->components.push_back(raycast6);
	entitys.back()->components.push_back(raycast7);
	entitys.back()->components.push_back(raycast8);
	entitys.back()->components.push_back(raycast9);
	entitys.back()->components.push_back(raycast10);
	entitys.back()->components.push_back(raycast11);
	entitys.back()->components.push_back(raycast12);
	entitys.back()->components.push_back(raycast13);
	entitys.back()->components.push_back(raycast14);
	entitys.back()->components.push_back(raycast15);
	entitys.back()->components.push_back(raycast16);
	entitys.back()->components.push_back(raycast17);
	entitys.back()->components.push_back(raycast18);
	entitys.back()->components.push_back(raycast19);
	entitys.back()->components.push_back(raycast20);
	entitys.back()->components.push_back(raycast21);
	entitys.back()->components.push_back(raycast22);
	entitys.back()->components.push_back(raycast23);
	entitys.back()->components.push_back(raycast24);
	entitys.back()->components.push_back(raycast25);
	entitys.back()->components.push_back(raycast26);
	entitys.back()->components.push_back(raycast27);
	entitys.back()->components.push_back(aim);
	aim->AssignNextNode(nodeMGR->nodes[node]->neighBours[0]);
	if (node == 0) {
		aim->previousNode = nodeMGR->nodes[nodeMGR->nodes.size() - 1];
	}
	else
	{
		aim->previousNode = nodeMGR->nodes[node - 1];
	}
	
	aim->LookAt();
	aim->LookAt();
	aim->LookAt();
	aim->LookAt();
	aim->LookAt();
}

void World::AddComponent(ComponentBase* component, int id) {	
	Entity* ent = entityID->FindEntity(id);
	ent->components.push_back(component);

}

ComponentBase* World::FindEmptyComponent(ComponentTypes type) {
	switch (type)
	{
	case TRANSFORM:
		for (auto comp : allo->transformAllocator.allocatedSpace)
		{
			
			if (comp->owner == NULL) {
					return comp;
			}
			
		}
		break;
	case CAMERA:
		for (auto comp : allo->cameraAllocator.allocatedSpace)
		{

			if (comp->owner == NULL) {
				return comp;
			}

		}
		break;
	case RIGIDBODY:
		break;
	case COLLISIONMESH:
		for (auto comp : allo->collisionAllocator.allocatedSpace)
		{

			if (comp->owner == NULL) {
				return comp;
			}

		}
		break;
	case CONTINUESFORCE:
		for (auto comp : allo->cmovementAllocator.allocatedSpace)
		{

			if (comp->owner == NULL) {
				return comp;
			}

		}
		break;
	case RENDERABLE:
		for (auto comp : allo->renderableAllocator.allocatedSpace)
		{

			if (comp->owner == NULL) {
				return comp;
			}

		}
		break;
	case AUDIOEMITER:
		break;
	case PARTICLEEMITTER:
		for (auto comp : allo->particleAllocator.allocatedSpace)
		{

			if (comp->owner == NULL) {
				return comp;
			}

		}
		break;
	case LIGHTSOURCE:
		break;
	case INPUT:
		for (auto comp : allo->inputAllocator.allocatedSpace)
		{

			if (comp->owner == NULL) {
				return comp;
			}

		}
		break;
	case RAYCAST:
		for (auto comp : allo->raycastAllocator.allocatedSpace)
		{

			if (comp->owner == NULL) {
				return comp;
			}

		}
		break;
	case AIMOVEMENT:
		for (auto comp : allo->aiAllocator.allocatedSpace)
		{

			if (comp->owner == NULL) {
				return comp;
			}

		}
		break;
	default:
		break;
	}
}