#include "Light.h"

Light::Light(glm::vec4 _color, glm::vec3 _position, float _intensity) : Object3D(), color(_color), intensity(_intensity)
{
	alive = true;
	SetPosition(_position);
}

Light::~Light()
{}

void Light::Update(double dt) {
	Object3D::Update(dt);
}

void Light::Init() {}
void Light::Draw() {}

float Light::GetIntensity() {
	return intensity;
}

glm::vec4 Light::GetColor(){
	return color;
}
