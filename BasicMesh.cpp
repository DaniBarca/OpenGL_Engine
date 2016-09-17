#include "BasicMesh.h"

BasicMesh::BasicMesh(string _path)
{
	this->path = _path;
}

BasicMesh::~BasicMesh()
{
}

void BasicMesh::Init() {
	Import3D(path);
	MeshObject::Init();

	reflectivity_diffuse = 0.9f;
	reflectivity_specular = 0.5f;
	reflectivity_ambient = 0.5f;
}

void BasicMesh::Update(double dt) {
	MeshObject::Update(dt);
}

void BasicMesh::Draw() {
	MeshObject::Draw();
}
