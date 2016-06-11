#pragma once

#include "Header.h"

class Mesh
{
	friend class MeshManager;

private:
	Mesh(GLfloat* _vertices, GLfloat* _vertices_normals, unsigned int _numVertices);
	~Mesh();

public:
	GLfloat* vertices;
	GLfloat* vertices_normals;
	unsigned int numVertices;
	bool inverted_normals;
};

