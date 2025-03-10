#include "config.h"
#include "Renderable.h"
#include "core/transform.h"
void Component::Renderable::Start() {
	type = RENDERABLE;
}
void Component::Renderable::Update(double dt) {
	Render::RenderDevice::Draw(modelId, ((Transform*)owner->FindComponent(TRANSFORM))->transform);
}

uint32_t Component::Renderable::id() {
	return 0 ;
}
Component::Renderable::Renderable() {

}

Component::Renderable::~Renderable() {

}