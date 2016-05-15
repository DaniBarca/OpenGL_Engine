#include "Light.h"

Light::Light(glm::vec3 _colour) : Object3D(), colour(_colour)
{}

Light::~Light()
{}

void Light::Update(double dt) {
	Object3D::Update(dt);
}
