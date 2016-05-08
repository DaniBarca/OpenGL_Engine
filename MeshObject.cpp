#include "MeshObject.h"

MeshObject::MeshObject() {
}

MeshObject::MeshObject(aiMesh* meshData) : MeshObject() {
}

void MeshObject::PrintVertices() {
	for (GLuint i = 0; i < (const unsigned int)(numVertices * 3); ++i) {
		std::cout << vertexBuffer[i];
		if ((i + 1) % 3 == 0)
			cout << endl;
		else
			cout << " -- ";
	}
}

void MeshObject::Init() : Object3D::Init(){

}

void MeshObject::Update(float dt) : Object3D::Update(dt){

}

void MeshObject::Draw() : Object3D::Draw(){

}
