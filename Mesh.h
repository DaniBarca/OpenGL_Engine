#pragma once

#include "Header.h"

class Mesh
{
	friend class MeshManager;

private:
	Mesh(GLfloat* _vertices, GLfloat* _normals, GLfloat* _uvs, unsigned int _numVertices, unsigned int _numNormals, unsigned int numUvs);
	~Mesh();

public:
	GLfloat* vertices;
	GLfloat* normals;
	GLfloat* uvs;
	
	unsigned int numVertices;
	unsigned int numNormals;
	unsigned int numUvs;

	bool inverted_normals;
};

