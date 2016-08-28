#pragma once

#include "Header.h"
#include "Light.h"
class RotatingLight : public Light
{
public:
	RotatingLight(glm::vec4 _color, glm::vec3 position, float _shininess, float _intensity = 1.0f);
	~RotatingLight();

	RotatingLight(const RotatingLight& l);

	void Update(double dt);
};

