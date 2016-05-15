#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Engine.h"
#include "Camera.h"

class MeshObject : public Object3D {
	GLfloat* vertices;
	GLfloat* polygon_normals;
	unsigned int numVertices;

	GLuint shaderID;
	GLuint matrixID;

	GLuint vertex_buffer;
	GLuint normal_buffer;

protected:
	bool Import3D(const string& path, bool invert_normals = false);

public:	
	MeshObject();
	MeshObject(aiMesh* meshData);

	void MeshObject::PrintVertices();

	void Init();
	void Update(double dt);
	void Draw();
};
