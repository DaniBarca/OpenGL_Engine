#pragma once

#include "Header.h"
#include "Light.h"

class SpotLight : public Light
{
	glm::vec3 direction;
	float angle;

public:
	SpotLight(glm::vec4 _color, glm::vec3 _position, float _shininess,  float _intensity, glm::vec3 _direction, float _angle);
	~SpotLight();

	glm::vec3 GetDirection();
	float GetAngle();
};

