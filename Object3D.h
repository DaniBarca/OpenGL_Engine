#pragma once

#include "Header.h"

class Object3D
{
	glm::mat4* transform;

public:
	Object3D();
	~Object3D();

	glm::mat4* Transform();

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
};

