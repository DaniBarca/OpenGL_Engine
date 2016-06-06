#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Color.h"

class Light : public Object3D
{
	Color color;
	float intensity;
	bool alive;
	
public:
	Light(Color _color, glm::vec3 position, float _intensity = 1.0f);
	~Light();

	void Update(double dt);

	void Init();
	void Draw();

	float GetIntensity();
};
