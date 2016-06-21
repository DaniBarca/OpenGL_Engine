#include "Teapot.h"

Teapot::Teapot() : MeshObject()
{}

Teapot::~Teapot()
{}

void Teapot::Init() {
	Import3D("models/teapot.obj");
	MeshObject::Init();

	reflectivity_diffuse = 1.0f;
	reflectivity_specular = 0.1f;
	reflectivity_ambient = 0.5f;

	specular_exponent = 20.0f;
}

void Teapot::Update(double dt) {
	MeshObject::Update(dt);
}

void Teapot::Draw() {
	MeshObject::Draw();
}
