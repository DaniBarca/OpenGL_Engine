#pragma once

#include "Header.h"
#include "Object3D.h"

class Light : public Object3D
{
	glm::vec3 colour;
	
public:
	Light(glm::vec3 _colour);
	~Light();

	void Update(double dt);
};

