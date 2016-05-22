#pragma once

#include "Header.h"

constexpr float I_256 = 1 / 256;

class Color : public glm::vec4
{
public:
	Color();
	Color(glm::vec4);
	Color(glm::vec3);
	Color(float, float, float);
	Color(float, float, float, float);

	~Color();
	
	Color clamp();
};

