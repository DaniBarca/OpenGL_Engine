#pragma once
#include "Header.h"
#include "Engine.h"

#define ZOOM_INDEX 0.02f
#define MOVE_INDEX 0.5f

class Camera
{
private:
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;

	Camera();
	~Camera();

	float fov;
	float aspect;
	float near;
	float far;
	float orbit_radius;
	double HFactor, VFactor;

public:
	static Camera* GetInstance();

	//void SetProjection(glm::mat4);
	void SetProjection();
	void SetView(glm::mat4);

	void ZoomIN();
	void ZoomOUT();
	void Closer();
	void Beyond();

	void setOrbitRadius(float);
	
	glm::vec3 GetPosition();

	//void Update(double dt);

	void Orbit();
	void Orbit(double HFactor, double VFactor, glm::vec3 around = glm::vec3(0, 0, 0));

	glm::mat4 getP();
	glm::mat4 getV();
};

