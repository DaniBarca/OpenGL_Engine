#pragma once

#include "Header.h"
#include "LightManager.h"

class ShadowMapper
{
	GLuint framebuffer_point, framebuffer_spot, framebuffer_directional;
	GLuint point_depth, spot_depth, directional_depth;

	size_t point_size, spot_size, directional_size;

	GLsizei resolution; // Width and height are expected to be the same

	void CheckBuffer();

public:
	static ShadowMapper* GetInstance();
	ShadowMapper();
	~ShadowMapper();

	void GenerateBuffer(unsigned int n_point, unsigned int n_spot, unsigned int n_directional);
	void GenerateMVPs(vector<Light*> point_lights, vector<Light*> spot_lights, vector<Light*> directional_lights);
};
