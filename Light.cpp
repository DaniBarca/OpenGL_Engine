#include "Light.h"

Light::Light(glm::vec4 _color, glm::vec3 _position, float _shininess, float _intensity, LIGHT_TYPE _type) : Object3D(), color(_color), intensity(_intensity), shininess(_shininess), type(_type)
{
	SetPosition(_position);
}

Light::~Light()
{}

void Light::Update(double dt) {
}

void Light::Init() {}
void Light::Draw() {}

float Light::GetIntensity() {
	return intensity;
}

float Light::GetShininess()
{
	return shininess;
}

glm::vec4 Light::GetColor(){
	return color;
}

LIGHT_TYPE Light::GetType()
{
	return type;
}
