#pragma once

#include "Header.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

class LightManager
{
	LightManager();
	~LightManager();

	vector<Light*> point_lights, spot_lights, directional_lights;

	/**
	       Point Light
               \|/
              --*--   <(o)>
               /|\  N  /
			  / | \ | /
	            ____.____
	 * */
	GLfloat* point_positions;
	GLfloat* point_intensities;
	GLfloat* point_colors;
	GLfloat* point_shininess;		//Exponent for specular lighting

	/**
	       Spot Light
                *     <(o)>
               /|\  N  /
			  / | \ | /
	            ____.____
	 * */
	GLfloat* spot_positions;
	GLfloat* spot_intensities;
	GLfloat* spot_colors;
	GLfloat* spot_shininess;
	GLfloat* spot_directions;
	GLfloat* spot_angles;

    /*
	         Directional Light
				*********
                |||||||||
                ||||||<(o)>
                |||||||/|
			    vvvvvv/vv
	            ____.____
	* */
	GLfloat* directional_positions;
	GLfloat* directional_intensities;
	GLfloat* directional_colors;
	GLfloat* directional_shininess;
	GLfloat* directional_directions;

	GLfloat* ambient_color;
	GLfloat ambient_intensity;
	GLfloat specular_exponent;
	
	void Compile();

	uint point_size, spot_size, directional_size, point_count, spot_count, directional_count;

public:
	static LightManager* GetInstance();
	LightManager* AllocLights(uint point_n, uint spot_n, uint dir_n);

	LightManager* Push(Light* l, LIGHT_TYPE type = LIGHT_TYPE::UNDEFINED);

	size_t GetNPointLights();
	size_t GetNSpotLights(); 
	size_t GetNDirectionalLights();

	void Update(double dt);

	GLfloat* GetPointPositions();
	GLfloat* GetPointIntensities();
	GLfloat* GetPointColors();
	GLfloat* GetPointShininess();

	GLfloat* GetSpotPositions();
	GLfloat* GetSpotIntensities();
	GLfloat* GetSpotColors();
	GLfloat* GetSpotShininess();
	GLfloat* GetSpotDirections();
	GLfloat* GetSpotAngles();

	GLfloat* GetDirectionalPositions();
	GLfloat* GetDirectionalIntensities();
	GLfloat* GetDirectionalColors();
	GLfloat* GetDirectionalShininess();
	GLfloat* GetDirectionalDirections();

	GLfloat* GetAmbientColor();
	GLfloat* GetAmbientItensity();
	
	LightManager* SetAmbientColor(glm::vec3 color);
	LightManager* SetAmbientItensity(float i);
};
