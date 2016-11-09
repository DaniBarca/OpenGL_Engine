#include "ShadowMapper.h"

void ShadowMapper::CheckBuffer()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		cout << "Failed to create shadowmap framebuffer" << endl;
		glfwTerminate();
		getchar();
		exit(EXIT_FAILURE);
	}
}

ShadowMapper* ShadowMapper::GetInstance() {
	static ShadowMapper* Instance = new ShadowMapper();
	return Instance;
}

ShadowMapper::ShadowMapper() {
	framebuffer_point       = 1;
	framebuffer_spot        = 2;
	framebuffer_directional = 3;

	point_size = spot_size = directional_size = 0;
	resolution = 1024;
}

ShadowMapper::~ShadowMapper() {}

void ShadowMapper::GenerateBuffer(unsigned int n_point, unsigned int n_spot, unsigned int n_directional) {
	/***********/
	/** Point **/
	/***********/
	if (n_point > point_size) {
		glGenFramebuffers(1, &framebuffer_point);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_point);

		glGenTextures(DIRECTION::NUM_DIRS * n_point, &point_depth);
		glBindTexture(GL_TEXTURE_2D, point_depth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, point_depth, 0);

		glDrawBuffer(GL_NONE);

		CheckBuffer();
		
		point_size = n_point;
	}

	/**********/
	/** Spot **/
	/**********/
	if (n_spot > spot_size) {
		glGenFramebuffers(1, &framebuffer_spot);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_spot);

		glGenTextures(DIRECTION::NUM_DIRS * n_spot, &spot_depth);
		glBindTexture(GL_TEXTURE_2D, spot_depth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, spot_depth, 0);

		glDrawBuffer(GL_NONE);

		CheckBuffer();

		spot_size = n_spot;
	}

	/*****************/
	/** Directional **/
	/*****************/
	if (n_directional > directional_size) {
		glGenFramebuffers(1, &framebuffer_directional);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_directional);

		glGenTextures(n_directional, &directional_depth);
		glBindTexture(GL_TEXTURE_2D, directional_depth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, directional_depth, 0);

		glDrawBuffer(GL_NONE);

		CheckBuffer();

		directional_size = n_directional;
	}
}

void ShadowMapper::GenerateMVPs(vector<Light*> point_lights, vector<Light*> spot_lights, vector<Light*> directional_lights) {
	glm::mat4x4* MVPs_point       = new glm::mat4x4[point_lights.size * DIRECTION::NUM_DIRS];
	glm::mat4x4* MVPs_spot        = new glm::mat4x4[spot_lights.size * DIRECTION::NUM_DIRS];
	glm::mat4x4* MVPs_directional = new glm::mat4x4[directional_lights.size];

	glm::mat4x4 M, V, P;

	for (size_t i = 0; i < point_lights.size; ++i) {
		for (unsigned int side = DIRECTION::FRONT; side < DIRECTION::NUM_DIRS; ++side) {
			M = point_lights[i]->Transform;
			V = glm::lookAt(DIRECTION_V[side], glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			P = 
			MVPs_point[i + side] = 
		}
	}

	for (size_t i = 0; i < spot_lights.size; ++i) {
		for (unsigned int side = DIRECTION::FRONT; side < DIRECTION::NUM_DIRS; ++side) {

		}
	}

	for (size_t i = 0; i < directional_lights.size; ++i) {
		
	}
}
