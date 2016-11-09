#pragma once

#include "Header.h"
#include "Mesh.h"

class MeshManager
{
private:
	MeshManager();
	~MeshManager();

	std::map<string, Mesh*> meshList;

public:
	static MeshManager* GetInstance();

	Mesh* LoadOBJ(const char * path);
	Mesh* LoadMesh(const string& path);
};

