#include "Light.h"

Light::Light(glm::vec4 _color, glm::vec3 _position, float _intensity, float _shinyness, LIGHT_TYPE _type) : Object3D(), color(_color), intensity(_intensity), shinyness(_shinyness), type(_type)
{
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

float Light::GetShinyness()
{
	return shinyness;
}

glm::vec4 Light::GetColor(){
	return color;
}

LIGHT_TYPE Light::GetType()
{
	return type;
}
