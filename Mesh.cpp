#include "Mesh.h"



Mesh::Mesh(GLfloat* _vertices, GLfloat* _vertices_normals, unsigned int _numVertices) : vertices(_vertices), vertices_normals(_vertices_normals), numVertices(_numVertices)
{}


Mesh::~Mesh()
{}
