#include "MeshObject.h"

MeshObject::MeshObject() {
}

MeshObject::MeshObject(aiMesh* meshData) : MeshObject() {
}

void MeshObject::PrintVertices() {
	for (GLuint i = 0; i < numVertices * 3; ++i) {
		std::cout << vertexBuffer[i] << " -- ";
		if ((i + 1) % 3 == 0)
			std::cout << endl;
	}
}
