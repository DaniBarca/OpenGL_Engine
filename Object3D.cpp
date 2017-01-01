#include "Object3D.h"

Object3D::Object3D() : transform(new glm::mat4())
{}

Object3D::~Object3D()
{
	delete transform;
}

glm::mat4* Object3D::Transform() {
	return transform;
}

void Object3D::Init() {}

//void Object3D::Update(double dt) {}

//void Object3D::Draw() {}

void Object3D::SetPosition(glm::vec3 position) {
	(*transform)[3][0] = position.x;
	(*transform)[3][1] = position.y;
	(*transform)[3][2] = position.z;
}

glm::vec3 Object3D::GetPosition() {
	return glm::vec3(
		(*transform)[3][0],
		(*transform)[3][1],
		(*transform)[3][2]
	);
}

glm::vec3 Object3D::GetRight() {
	return glm::vec3(
		(*transform)[0][0],
		(*transform)[1][0],
		(*transform)[2][0]
	);
}

glm::vec3 Object3D::GetUp() {
	return glm::vec3(
		(*transform)[0][1],
		(*transform)[1][1],
		(*transform)[2][1]
	);
}

glm::vec3 Object3D::GetForward() {
	return glm::vec3(
		(*transform)[0][2],
		(*transform)[1][2],
		(*transform)[2][2]
	);
}

void Object3D::SetRotation(float angle, glm::vec3 axis)
{
	*transform = glm::rotate(angle, axis);
}

void Object3D::Rotate(float angle, glm::vec3 axis){
	*transform = glm::rotate(*transform, angle, axis);
}
