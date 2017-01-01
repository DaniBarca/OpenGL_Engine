#include "BasicMesh.h"

BasicMesh::BasicMesh(string _path, string _texture_path)
{
	this->path = _path;
	this->texture_path = _texture_path;
}

BasicMesh::~BasicMesh()
{
}

void BasicMesh::Init() {
	Import3D(path);
	ImportTexture(texture_path);

	MeshObject::Init();

	reflectivity_diffuse = 0.9f;
	reflectivity_specular = 0.5f;
	reflectivity_ambient = 0.5f;
}
