#pragma once

#include "Header.h"
#include "Light.h"

class LightManager
{
	LightManager();
	~LightManager();

	vector<Light*> lights;

public:
	static LightManager* GetInstance();
	LightManager* Push(Light* l);

	Light* GetLight(unsigned int pos);

	void Update(float dt);
};
