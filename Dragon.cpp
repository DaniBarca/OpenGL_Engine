#include "Dragon.h"

Dragon::Dragon() : MeshObject()
{}


Dragon::~Dragon()
{}

void Dragon::Init() {
	Import3D("models/dragon.obj", true);
	MeshObject::Init();
}

void Dragon::Update(double dt) {
	MeshObject::Update(dt);
}

void Dragon::Draw() {
	MeshObject::Draw();
}
