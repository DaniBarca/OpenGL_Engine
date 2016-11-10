#include "Mesh.h"



Mesh::Mesh(GLfloat* _vertices, GLfloat* _normals, GLfloat* _uvs, unsigned int _numVertices, unsigned int _numNormals, unsigned int _numUvs) : vertices(_vertices), normals(_normals), uvs(_uvs), numVertices(_numVertices), numNormals(_numNormals), numUvs(_numUvs)
{}


Mesh::~Mesh()
{}
