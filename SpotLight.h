#pragma once

#include "Header.h"
#include "Light.h"

class SpotLight : public Light
{
	glm::vec3 direction;
	glm::vec3 angle;

public:
	SpotLight(glm::vec4 _color, glm::vec3 _position, float _intensity, float _shininess, LIGHT_TYPE _type, glm::vec3 _direction, glm::vec3 _angle);
	~SpotLight();

	glm::vec3 GetDirection();
	glm::vec3 GetAngle();
};

