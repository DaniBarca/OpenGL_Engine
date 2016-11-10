#pragma once

#include "Header.h"
#include "Mesh.h"

class MeshManager
{
private:
	MeshManager();
	~MeshManager();

	std::unordered_map<string, Mesh*> meshList;

public:
	static MeshManager* GetInstance();

	Mesh* LoadOBJ(const char * path);
	void GenerateBin(const char* path, Mesh* m);
	Mesh* LoadMesh_OBJ(const char * path);
	Mesh* LoadMesh_BIN(const char* path);
};

