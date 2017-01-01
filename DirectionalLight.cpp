#include "DirectionalLight.h"



DirectionalLight::DirectionalLight(glm::vec4 _color, glm::vec3 _position, float _shininess, float _intensity, glm::vec3 _direction) : direction(_direction), Light(_color, _position, _shininess, _intensity, LIGHT_TYPE::DIRECTIONAL)
{
	glm::vec3 up;
	if (std::abs(_direction.x) < 0.00001f &&
		(std::abs(_direction.y) - 1.0f) < 0.00001f &&
		std::abs(_direction.z) < 0.00001f){
		up = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	else {
		up = glm::cross(_direction, V_UP);
	}

	*transform = glm::lookAt(
		_direction,
		_position,
		up
	);
}


DirectionalLight::~DirectionalLight()
{
	Light::~Light();
}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}
