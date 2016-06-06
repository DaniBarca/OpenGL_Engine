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

void Object3D::Update(double dt) {}

void Object3D::Draw() {}

void Object3D::SetPosition(glm::vec3 position) {
	(*transform)[3][0] = position.x;
	(*transform)[3][1] = position.y;
	(*transform)[3][2] = position.z;
}

glm::vec3 Object3D::GetPosition() {
	return glm::vec3((*transform)[3]);
}
