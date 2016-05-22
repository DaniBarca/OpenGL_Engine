#include "Teapot.h"

Teapot::Teapot() : MeshObject()
{}

Teapot::~Teapot()
{}

void Teapot::Init() {
	Import3D("models/teapot.obj",true);
	MeshObject::Init();
	material.setDiffuseColor(Color(246.0f, 247.0f, 248.0f));
}

void Teapot::Update(double dt) {
	MeshObject::Update(dt);
}

void Teapot::Draw() {
	MeshObject::Draw();
}
