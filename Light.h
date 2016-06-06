#pragma once

#include "Header.h"
#include "Object3D.h"

class Light : public Object3D
{
	glm::vec4 color;
	float intensity;
	bool alive;
	
public:
	Light(glm::vec4 _color, glm::vec3 position, float _intensity = 1.0f);
	~Light();

	void Update(double dt);

	void Init();
	void Draw();

	float GetIntensity();
	glm::vec4 GetColor();
};
