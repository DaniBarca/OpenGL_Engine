#pragma once

#include "Header.h"
#include "Light.h"

class DirectionalLight : public Light
{
	glm::vec3 direction;

public:
	DirectionalLight(glm::vec4 _color, glm::vec3 _position, float _shininess, float _intensity, glm::vec3 _direction);
	~DirectionalLight();

	glm::vec3 GetDirection();
};

