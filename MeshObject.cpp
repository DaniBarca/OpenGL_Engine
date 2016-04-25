#include "MeshObject.h"

MeshObject::MeshObject() {
	//vertices = vector< glm::vec3 >();
}

MeshObject::MeshObject(aiMesh* meshData) : MeshObject() {
	Import(meshData);
}

void MeshObject::Import(aiMesh* meshData){
	vertices = (GLfloat*)(meshData->mVertices);
	numVertices = meshData->mNumVertices;
}
