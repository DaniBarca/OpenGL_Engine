#include "SpotLight.h"



SpotLight::SpotLight(glm::vec4 _color, glm::vec3 _position, float _intensity, float _shininess, LIGHT_TYPE _type, glm::vec3 _direction, glm::vec3 _angle) : direction(_direction), angle(_angle), Light(_color, _position, _intensity, _shininess, _type)
{}


SpotLight::~SpotLight()
{
	Light::~Light();
}

glm::vec3 SpotLight::GetDirection()
{
	return direction;
}

glm::vec3 SpotLight::GetAngle()
{
	return angle;
}
