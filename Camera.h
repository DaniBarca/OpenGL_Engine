#pragma once
#include "Header.h"
#include "Engine.h"

#define ZOOM_INDEX 0.02f
#define MOVE_INDEX 0.5f

class Camera
{
	glm::mat4 projection;
	glm::mat4 view;

	glm::mat4 PV;

	Camera();
	~Camera();

	float fov;
	float aspect;
	float near;
	float far;
	float orbit_radius;
	double HFactor, VFactor;

public:
	static Camera* getInstance();

	//void SetProjection(glm::mat4);
	void SetProjection();
	void SetView(glm::mat4);

	void ZoomIN();
	void ZoomOUT();
	void Closer();
	void Beyond();

	void setOrbitRadius(float);
	

	//void Update(double dt);

	void Orbit();
	void Orbit(double HFactor, double VFactor, glm::vec3 around = glm::vec3(0, 0, 0));

	glm::mat4 getPV();
};

