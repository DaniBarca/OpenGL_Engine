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
	GLfloat* colors;

	GLfloat ambient_intensity;
	GLfloat specular_exponent;
	
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
	GLfloat* GetColors();

	GLfloat* GetAmbientItensity();
	GLfloat* GetSpecularExponent();
	
	LightManager* SetAmbientItensity(float i);
	LightManager* SetSpecularExponent(float e);
};
