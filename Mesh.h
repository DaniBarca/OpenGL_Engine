#pragma once

#include "Header.h"

class Mesh
{
	friend class MeshManager;

private:
	Mesh(GLfloat* _vertices, GLfloat* _normals, GLfloat* _uvs, uint _numVertices, uint _numNormals, uint numUvs);
	~Mesh();

public:
	GLfloat* vertices;
	GLfloat* normals;
	GLfloat* uvs;
	
	uint numVertices;
	uint numNormals;
	uint numUvs;

	bool inverted_normals;
};

