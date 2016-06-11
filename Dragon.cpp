#include "Dragon.h"

Dragon::Dragon() : MeshObject()
{}


Dragon::~Dragon()
{}

void Dragon::Init() {
	Import3D("models/dragon.obj");
	MeshObject::Init();

	reflectivity_diffuse = 0.5f;
	reflectivity_specular = 0.8f;
	reflectivity_ambient = 0.5f;
}

void Dragon::Update(double dt) {
	MeshObject::Update(dt);
}

void Dragon::Draw() {
	MeshObject::Draw();
}
