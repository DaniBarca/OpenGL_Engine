#include "Light.h"

Light::Light(Color _color, glm::vec3 _position, float _intensity) : Object3D(), color(_color), intensity(_intensity)
{
	alive = true;
	glm::translate(*Transform(), _position);
}

Light::~Light()
{}

void Light::Update(double dt) {
	Object3D::Update(dt);
}

void Light::Init() {}
void Light::Draw() {}
