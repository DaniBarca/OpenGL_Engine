#include "Camera.h"

Camera::Camera()
{
	fov    = 45.0f;
	aspect = 4.0f / 3.0f;
	near   = 0.1f;
	far    = 100.0f;
	
	orbit_radius = 25.0f;

	HFactor = 0.0f;
	VFactor = 0.0f;

	projection = glm::perspective(fov, aspect, near, far);
	Orbit(0.0f, 0.0f);
	
}

Camera::~Camera()
{
}

Camera* Camera::getInstance(){
	static Camera* Instance = new Camera();
	return Instance;
}

/*void Camera::SetProjection(glm::mat4 p) {
	projection = p;
	PV = projection * view;
}*/

void Camera::SetProjection() {
	projection = glm::perspective(fov, aspect, near, far);
	PV = projection * view;
}

void Camera::SetView(glm::mat4 v) {
	view = v;
	PV = projection * view;
}

void Camera::ZoomIN() {
	fov -= ZOOM_INDEX;
	SetProjection();
}

void Camera::ZoomOUT() {
	fov += ZOOM_INDEX;
	SetProjection();
}

void Camera::Closer() {
	orbit_radius -= MOVE_INDEX;
	Orbit();
}

void Camera::Beyond() {
	orbit_radius += MOVE_INDEX;
	Orbit();
	cout << orbit_radius << endl;
}

void Camera::setOrbitRadius(float radius) {
	orbit_radius = radius;
}

void Camera::Orbit() {
	this->Orbit(this->HFactor, this->VFactor);
}

void Camera::Orbit(double HFactor, double VFactor, glm::vec3 around) {
	this->HFactor = HFactor;
	this->VFactor = VFactor;
	SetView(
		glm::lookAt(
			glm::vec3(
				2.0f * orbit_radius * glm::sin(HFactor),
				2.0f * orbit_radius * glm::sin(VFactor),
				2.0f * orbit_radius * glm::cos(HFactor)
			),
			around,
			V_UP
		)
	);
}

glm::mat4 Camera::getPV() {
	return PV;
}
