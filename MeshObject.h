#pragma once

#include "Header.h"

class MeshObject {
	GLfloat* vertexBuffer;
	int numVertices;
public:
	MeshObject();
	MeshObject(aiMesh* meshData);

	void Import(aiMesh* meshData);
};
