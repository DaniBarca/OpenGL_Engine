#include "FlatPlane.h"

FlatPlane::FlatPlane()
{
}

FlatPlane::~FlatPlane()
{
}

void FlatPlane::Init() {
	Import3D("models/flat.obj");
	MeshObject::Init();

	reflectivity_diffuse = 0.9f;
	reflectivity_specular = 0.5f;
	reflectivity_ambient = 0.5f;
}

void FlatPlane::Update(double dt) {
	MeshObject::Update(dt);
}

void FlatPlane::Draw() {
	MeshObject::Draw();
}
