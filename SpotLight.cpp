#include "SpotLight.h"



SpotLight::SpotLight(glm::vec4 _color, glm::vec3 _position, float _shininess, float _intensity, glm::vec3 _direction, float _angle) : direction(_direction), angle(_angle), Light(_color, _position, _intensity, _shininess, LIGHT_TYPE::SPOT)
{}


SpotLight::~SpotLight()
{
	Light::~Light();
}

glm::vec3 SpotLight::GetDirection()
{
	return direction;
}

float SpotLight::GetAngle()
{
	return angle;
}
