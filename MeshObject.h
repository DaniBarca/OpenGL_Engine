#pragma once

#include "Header.h"

class MeshObject {
public:
	GLfloat* vertexBuffer;
	int numVertices;
	
	MeshObject();
	MeshObject(aiMesh* meshData);

	void Import(aiMesh* meshData);
};
