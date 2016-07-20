#pragma once

#include "Header.h"
#include "Object3D.h"

typedef enum LIGHT_TYPE {
	POINT = 0,
	DIRECTIONAL,
	SPOT,
	AREA
} LIGHT_TYPE;

class Light : public Object3D
{
	glm::vec4 color;
	float intensity, shininess;
	LIGHT_TYPE type;
		
public:
	Light(glm::vec4 _color, glm::vec3 _position, float _shininess, float _intensity = 1.0f, LIGHT_TYPE _type = LIGHT_TYPE::POINT);
	~Light();

	void Update(double dt);

	void Init();
	void Draw();

	float GetIntensity();
	float GetShininess();
	glm::vec4 GetColor();
	LIGHT_TYPE GetType();
};
