#pragma once

#include "Header.h"
#include "Light.h"
class RotatingLight : public Light
{
public:
	RotatingLight(Color _color, glm::vec3 position, float _intensity = 1.0f);
	~RotatingLight();

	RotatingLight(const RotatingLight& l);

	void Update(double dt);
};

