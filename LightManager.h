#pragma once

#include "Header.h"
#include "Light.h"

class LightManager
{
	LightManager();
	~LightManager();

	vector<Light*> lights;

public:
	static LightManager* AllocLights(int n_lights);
	static LightManager* GetInstance();
	LightManager* Push(Light* l);

	Light* GetLight(unsigned int pos);

	size_t GetNLights();

	void Update(float dt);
};
