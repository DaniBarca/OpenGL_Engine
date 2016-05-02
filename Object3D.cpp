#include "Object3D.h"



Object3D::Object3D() : transform(new glm::mat4())
{}


Object3D::~Object3D()
{}

glm::mat4* Object3D::Transform() {
	return transform;
}
