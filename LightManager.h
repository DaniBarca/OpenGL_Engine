#pragma once

#include "Header.h"
#include "Light.h"

class LightManager
{
	LightManager();
	~LightManager();

	vector<Light*> point_lights, spot_lights, directional_lights;

	GLfloat* point_positions;
	GLfloat* point_intensities;
	GLfloat* point_colors;
	GLfloat* point_shinyness;

	GLfloat* spot_positions;
	GLfloat* spot_intensities;
	GLfloat* spot_colors;
	GLfloat* spot_shinyness;
	GLfloat* spot_directions;
	GLfloat* spot_angles;

	GLfloat* directional_positions;
	GLfloat* directional_intensities;
	GLfloat* directional_colors;
	GLfloat* directional_shinyness;
	GLfloat* directional_directions;

	GLfloat ambient_intensity;
	GLfloat specular_exponent;
	
	void Compile();

	int point_size, spot_size, directional_size;

public:
	static LightManager* GetInstance();
	LightManager* AllocLights(int point_n, int spot_n, int dir_n);

	LightManager* Push(Light* l, LIGHT_TYPE type = LIGHT_TYPE::POINT);

	size_t GetNPointLights();
	size_t GetNSpotLights(); 
	size_t GetNDirectionalLights();

	void Update(double dt);

	GLfloat* GetPointPositions();
	GLfloat* GetPointIntensities();
	GLfloat* GetPointColors();
	GLfloat* GetPointShinyness();

	GLfloat* GetSpotPositions();
	GLfloat* GetSpotIntensities();
	GLfloat* GetSpotColors();
	GLfloat* GetSpotShinyness();
	GLfloat* GetSpotDirections();
	GLfloat* GetSpotAngles();

	GLfloat* GetDirectionalPositions();
	GLfloat* GetDirectionalIntensities();
	GLfloat* GetDirectionalColors();
	GLfloat* GetDirectionalShinyness();
	GLfloat* GetDirectionalDirections();

	GLfloat* GetAmbientItensity();
	
	LightManager* SetAmbientItensity(float i);
	LightManager* SetSpecularExponent(float e);
};
