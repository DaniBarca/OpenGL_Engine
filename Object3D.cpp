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
