#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Color.h"

class Light : public Object3D
{
	Color color;
	float intensity;
	
public:
	Light(Color _color, float _intensity = 1.0f);
	~Light();

	void Update(double dt);
};

