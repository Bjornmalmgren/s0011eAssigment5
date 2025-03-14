//------------------------------------------------------------------------------
// spacegameapp.cc
// (C) 2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "spacegameapp.h"
#include <cstring>
#include "imgui.h"
#include "render/renderdevice.h"
#include "render/shaderresource.h"
#include <vector>
#include "render/textureresource.h"
#include "render/model.h"
#include "render/cameramanager.h"
#include "render/lightserver.h"
#include "render/debugrender.h"
#include "core/random.h"
#include "render/input/inputserver.h"
#include "core/cvar.h"
#include "render/physics.h"
#include <chrono>
#include "spaceship.h"
#include "core/World.h"
#include "render/NodeManager.h"
#include "core/AiManager.h"
using namespace Display;
using namespace Render;
using namespace Component;
namespace Game
{

//------------------------------------------------------------------------------
/**
*/
SpaceGameApp::SpaceGameApp()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
SpaceGameApp::~SpaceGameApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
bool
SpaceGameApp::Open()
{
	App::Open();
	this->window = new Display::Window;
    this->window->SetSize(1920, 1080);

    if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        RenderDevice::Init();

		// set ui rendering function
		this->window->SetUiRender([this]()
		{
			this->RenderUI();
		});
        
        return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
SpaceGameApp::Run()
{
    World world;
    int w;
    int h;
    this->window->GetSize(w, h);
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), float(w) / float(h), 0.01f, 1000.f);
    Camera* cam = CameraManager::GetCamera(CAMERA_MAIN);
    cam->projection = projection;
    

    // load all resources
    ModelId models[6] = {
        LoadModel("assets/space/Asteroid_1.glb"),
        LoadModel("assets/space/Asteroid_2.glb"),
        LoadModel("assets/space/Asteroid_3.glb"),
        LoadModel("assets/space/Asteroid_4.glb"),
        LoadModel("assets/space/Asteroid_5.glb"),
        LoadModel("assets/space/Asteroid_6.glb")
    };
    Physics::ColliderMeshId colliderMeshes[6] = {
        Physics::LoadColliderMesh("assets/space/Asteroid_1_physics.glb"),
        Physics::LoadColliderMesh("assets/space/Asteroid_2_physics.glb"),
        Physics::LoadColliderMesh("assets/space/Asteroid_3_physics.glb"),
        Physics::LoadColliderMesh("assets/space/Asteroid_4_physics.glb"),
        Physics::LoadColliderMesh("assets/space/Asteroid_5_physics.glb"),
        Physics::LoadColliderMesh("assets/space/Asteroid_6_physics.glb")
    };

    //std::vector<std::tuple<ModelId, Physics::ColliderId, glm::mat4>> asteroids;
    std::vector<Entity*> a;
    // Setup asteroids near
    
    for (int i = 0; i < 100; i++)
    {
        //Entity* as = new Entity();
        world.CreateEntity();
        //a.push_back(as);
       
        Renderable* render = (Renderable*)world.FindEmptyComponent(RENDERABLE);
;
        render->owner = world.FindEntity(i+1);
        //render->owner = a[i];
        
        Transform* transf = (Transform*)world.FindEmptyComponent(TRANSFORM);

        transf->owner = world.FindEntity(i + 1);

        Component::CollisionMesh* collison = (CollisionMesh*)world.FindEmptyComponent(COLLISIONMESH);
        collison->owner = world.FindEntity(i + 1);
        
        Component::ContinuesMovement* cMovement = (Component::ContinuesMovement*)world.FindEmptyComponent(CONTINUESFORCE);
        cMovement->owner = world.FindEntity(i + 1);
        cMovement->rotZ = 1;
        size_t resourceIndex = (size_t)(Core::FastRandom() % 6);

        render->modelId = models[resourceIndex];
        float span = 60.0f;
        glm::vec3 translation = glm::vec3(
            Core::RandomFloatNTP() * span,
            Core::RandomFloatNTP() * span,
            Core::RandomFloatNTP() * span
        );
        glm::vec3 rotationAxis = normalize(translation);
        float rotation = translation.x;
        glm::mat4 transform = glm::rotate(rotation, rotationAxis) * glm::translate(translation);
        collison->colliderID = Physics::CreateCollider(colliderMeshes[resourceIndex], transform);
        transf->transform = transform;

        world.AddComponent(render, world.FindEntity(i + 1)->id);
        world.AddComponent(transf, world.FindEntity(i + 1)->id);
        world.AddComponent(collison, world.FindEntity(i + 1)->id);
        world.AddComponent(cMovement, world.FindEntity(i + 1)->id);
        //a[i]->components.push_back(render);
        //a[i]->components.push_back(transf);
        //a[i]->components.push_back(collison);

       
    }

    // Setup asteroids far
    for (int i = 0; i < 50; i++)
    {
        //Entity* as = new Entity();
        world.CreateEntity();

  
        Renderable* render = (Renderable*)world.FindEmptyComponent(RENDERABLE);
        ;
        render->owner = world.FindEntity(i + 101);
        //render->owner = a[i];

        Transform* transf = (Transform*)world.FindEmptyComponent(TRANSFORM);

        transf->owner = world.FindEntity(i + 101);

        Component::CollisionMesh* collison = (CollisionMesh*)world.FindEmptyComponent(COLLISIONMESH);
        collison->owner = world.FindEntity(i + 101);

        Component::ContinuesMovement* cMovement = (Component::ContinuesMovement*)world.FindEmptyComponent(CONTINUESFORCE);
        cMovement->owner = world.FindEntity(i + 101);
        cMovement->rotZ = 1.5;

        size_t resourceIndex = (size_t)(Core::FastRandom() % 6);
        render->modelId = models[resourceIndex];

        float span = 130.0f;
        glm::vec3 translation = glm::vec3(
            Core::RandomFloatNTP() * span,
            Core::RandomFloatNTP() * span,
            Core::RandomFloatNTP() * span
        );
        glm::vec3 rotationAxis = normalize(translation);
        float rotation = translation.x;
        glm::mat4 transform = glm::rotate(rotation, rotationAxis) * glm::translate(translation);
       
        collison->colliderID = Physics::CreateCollider(colliderMeshes[resourceIndex], transform);
        transf->transform = transform;

        world.AddComponent(render, world.FindEntity(i  + 101)->id);
        world.AddComponent(transf, world.FindEntity(i  + 101)->id);
        world.AddComponent(collison, world.FindEntity(i  + 101)->id);
        world.AddComponent(cMovement, world.FindEntity(i + 101)->id);
        //a.push_back(as);
    }
  
    
    // Setup skybox
    std::vector<const char*> skybox
    {
        "assets/space/bg.png",
        "assets/space/bg.png",
        "assets/space/bg.png",
        "assets/space/bg.png",
        "assets/space/bg.png",
        "assets/space/bg.png"
    };
    TextureResourceId skyboxId = TextureResource::LoadCubemap("skybox", skybox, true);
    RenderDevice::SetSkybox(skyboxId);
    
    Input::Keyboard* kbd = Input::GetDefaultKeyboard();

    const int numLights = 40;
    Render::PointLightId lights[numLights];
    // Setup lights
    for (int i = 0; i < numLights; i++)
    {
        glm::vec3 translation = glm::vec3(
            Core::RandomFloatNTP() * 20.0f,
            Core::RandomFloatNTP() * 20.0f,
            Core::RandomFloatNTP() * 20.0f
        );
        glm::vec3 color = glm::vec3(
            Core::RandomFloat(),
            Core::RandomFloat(),
            Core::RandomFloat()
        );
        lights[i] = Render::LightServer::CreatePointLight(translation, color, Core::RandomFloat() * 4.0f, 1.0f + (15 + Core::RandomFloat() * 10.0f));
    }

    nodeMGR->createNode(glm::vec3(0, 0, 0)); 
    nodeMGR->createNode(glm::vec3(28, 2, 22));
    nodeMGR->createNode(glm::vec3(-7, 21, 41));

    nodeMGR->createNode(glm::vec3(-10, 38, 22));
    nodeMGR->createNode(glm::vec3(-13, -69, 28));
    nodeMGR->createNode(glm::vec3(-3, 32, -44));

    nodeMGR->createNode(glm::vec3(8, -13, -33));
    nodeMGR->createNode(glm::vec3(-3, -35, -34));
    nodeMGR->createNode(glm::vec3(47, -43, 10));

    nodeMGR->createNode(glm::vec3(43, -60, -12));
    nodeMGR->createNode(glm::vec3(23, -56, -60));
    nodeMGR->createNode(glm::vec3(8, -38, -62));
    nodeMGR->createNode(glm::vec3(48, -9, -41));

    nodeMGR->nodes[0]->neighBours.push_back(nodeMGR->nodes[1]);
    nodeMGR->nodes[1]->neighBours.push_back(nodeMGR->nodes[2]);
    nodeMGR->nodes[2]->neighBours.push_back(nodeMGR->nodes[3]);

    nodeMGR->nodes[3]->neighBours.push_back(nodeMGR->nodes[4]);
    nodeMGR->nodes[4]->neighBours.push_back(nodeMGR->nodes[5]);
    nodeMGR->nodes[5]->neighBours.push_back(nodeMGR->nodes[6]);

    nodeMGR->nodes[6]->neighBours.push_back(nodeMGR->nodes[7]);
    nodeMGR->nodes[7]->neighBours.push_back(nodeMGR->nodes[8]);
    nodeMGR->nodes[8]->neighBours.push_back(nodeMGR->nodes[9]);

    nodeMGR->nodes[9]->neighBours.push_back(nodeMGR->nodes[10]);
    nodeMGR->nodes[10]->neighBours.push_back(nodeMGR->nodes[11]);
    nodeMGR->nodes[11]->neighBours.push_back(nodeMGR->nodes[12]);
    nodeMGR->nodes[12]->neighBours.push_back(nodeMGR->nodes[0]);

    world.CreateSpaceShip();
    world.CreateAISpaceShip();
    AIManager->AI1 = world.entitys.back();

    world.StartEntitys();
    std::clock_t c_start = std::clock();
    double dt = 0.01667f;
    
    // game loop
    while (this->window->IsOpen())
	{
        auto timeStart = std::chrono::steady_clock::now();
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
        
        this->window->Update();

        if (kbd->pressed[Input::Key::Code::End])
        {
            ShaderResource::ReloadShaders();
        }

        

        // Draw some debug text
        Debug::DrawDebugText("FOOBAR", glm::vec3(0), {1,0,0,1});
        if (nodeMGR->draw == true) {
            nodeMGR->DrawNodes(nodeMGR->draw);
        }
        if (nodeMGR->addNode == true) {
            nodeMGR->addNode = false;
            nodeMGR->createNode(((Transform*)world.player->FindComponent(TRANSFORM))->position);
            nodeMGR->nodes.back()->neighBours.push_back(nodeMGR->nodes[nodeMGR->nodes.size()-2]);
        }
        
        world.UpdateEntitys(dt);
        if (AIManager->AI1 != NULL) {
            if (AIManager->AI1->Destroyed == true) {
                AIManager->AI1 = NULL;
            }


        }
        
        // Execute the entire rendering pipeline
        RenderDevice::Render(this->window, dt);

		// transfer new frame to window
		this->window->SwapBuffers();

        auto timeEnd = std::chrono::steady_clock::now();
        dt = std::min(0.04, std::chrono::duration<double>(timeEnd - timeStart).count());

        if (kbd->pressed[Input::Key::Code::Escape])
            this->Exit();
	}
}

//------------------------------------------------------------------------------
/**
*/
void
SpaceGameApp::Exit()
{

    this->window->Close();
}

//------------------------------------------------------------------------------
/**
*/

void
SpaceGameApp::RenderUI()
{
	if (this->window->IsOpen())
	{
        ImGui::Begin("Debug");
        Core::CVar* r_draw_light_spheres = Core::CVarGet("r_draw_light_spheres");
        int drawLightSpheres = Core::CVarReadInt(r_draw_light_spheres);
        if (ImGui::Checkbox("Draw Light Spheres", (bool*)&drawLightSpheres))
            Core::CVarWriteInt(r_draw_light_spheres, drawLightSpheres);
        
        Core::CVar* r_draw_light_sphere_id = Core::CVarGet("r_draw_light_sphere_id");
        int lightSphereId = Core::CVarReadInt(r_draw_light_sphere_id);
        if (ImGui::InputInt("LightSphereId", (int*)&lightSphereId))
            Core::CVarWriteInt(r_draw_light_sphere_id, lightSphereId);
        

        ImGui::End();

        ImGui::Begin("Draw Nodes");
        bool draw = nodeMGR->draw;
        
        if (ImGui::Button("Add node")) {
            nodeMGR->addNode = true;
        }
        bool im = ImGui::Checkbox("Draw Nodes", &draw);
        if (AIManager->AI1 != NULL) {
            ImGui::InputFloat("PosX", &((Transform*)AIManager->AI1->FindComponent(TRANSFORM))->position.x);
            ImGui::InputFloat("PosY", &((Transform*)AIManager->AI1->FindComponent(TRANSFORM))->position.y);
            ImGui::InputFloat("PosZ", &((Transform*)AIManager->AI1->FindComponent(TRANSFORM))->position.z);
            ImGui::InputFloat("Speed", &((AiMovement*)AIManager->AI1->FindComponent(AIMOVEMENT))->currentSpeed);
            ImGui::InputInt("Slowing", &((AiMovement*)AIManager->AI1->FindComponent(AIMOVEMENT))->slowing);
            ImGui::InputInt("Near a node", &((AiMovement*)AIManager->AI1->FindComponent(AIMOVEMENT))->nearNode);

            
        } 
        nodeMGR->draw = draw;
        ImGui::End();
        Debug::DispatchDebugTextDrawing();
	}
}

} // namespace Game