#include "MeshObject.h"

MeshObject::MeshObject() {
}

MeshObject::MeshObject(aiMesh* meshData) : MeshObject() {
	Import(meshData);
}

void MeshObject::Import(aiMesh* mesh){
	vertexBuffer = new GLfloat[mesh->mNumVertices * VERTICES_PER_POL];// (GLfloat*)malloc(sizeof(GLfloat) * mesh->mNumVertices * VERTICES_PER_POL);

	for (GLuint i = 0; i < mesh->mNumVertices; ++i) {
		vertexBuffer[i * VERTICES_PER_POL + 0] = mesh->mVertices[i].x;
		vertexBuffer[i * VERTICES_PER_POL + 1] = mesh->mVertices[i].y;
		vertexBuffer[i * VERTICES_PER_POL + 2] = mesh->mVertices[i].z;
	}
}
