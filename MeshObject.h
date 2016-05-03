#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Import.h"

class MeshObject : public Object3D {
	friend bool Import3D(const string& path, MeshObject*& meshes);

	GLfloat* vertexBuffer;
	unsigned int numVertices;

public:	
	MeshObject();
	MeshObject(aiMesh* meshData);

	void MeshObject::PrintVertices();
};
