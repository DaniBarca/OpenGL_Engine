#pragma once

#include "Header.h"

class MeshObject {
	GLfloat* vertices;
	int numVertices;
public:
	MeshObject();
	MeshObject(aiMesh* meshData);

	void Import(aiMesh* meshData);
};
