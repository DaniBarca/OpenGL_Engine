#pragma once

#include "Header.h"

class Object3D
{
protected:
	glm::mat4* transform;

public:
	Object3D();
	~Object3D();

	glm::mat4* Transform();

	virtual void Init() = 0;
//	virtual void Update(double dt) = 0;
//	virtual void Draw() = 0;

	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition();

	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::vec3 GetForward();

	void SetRotation(float angle, glm::vec3 axis);
	void Rotate(float angle, glm::vec3 axis);
};

