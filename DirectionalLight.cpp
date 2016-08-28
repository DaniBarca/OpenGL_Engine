#include "DirectionalLight.h"



DirectionalLight::DirectionalLight(glm::vec4 _color, glm::vec3 _position, float _shininess, float _intensity, glm::vec3 _direction) : direction(_direction), Light(_color, _position, _intensity, _shininess, LIGHT_TYPE::DIRECTIONAL)
{
}


DirectionalLight::~DirectionalLight()
{
	Light::~Light();
}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}
