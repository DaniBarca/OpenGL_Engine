#pragma once

#include "Header.h"
#include "Light.h"

class LightManager
{
	LightManager();
	~LightManager();

	vector<Light*> lights;

	GLfloat* positions;
	GLfloat* intensities;
	
	void Compile();

public:
	static LightManager* GetInstance();
	LightManager* AllocLights(int n_lights);

	LightManager* Push(Light* l);

	Light* GetLight(unsigned int pos);

	size_t GetNLights();

	void Update(double dt);

	GLfloat* GetPositions();
	GLfloat* GetIntensities();
};
