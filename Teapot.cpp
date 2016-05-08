#include "Teapot.h"

Teapot::Teapot() : MeshObject()
{}

Teapot::~Teapot()
{}

void Teapot::Init() {
	Import3D("models/teapot.obj");
	MeshObject::Init();
}

void Teapot::Update(double dt) {
	MeshObject::Update(dt);
}

void Teapot::Draw() {
	MeshObject::Draw();
}
