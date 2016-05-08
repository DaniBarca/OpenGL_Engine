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

bool MeshObject::Import3D(const string& path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (!scene) {
		cout << "Error while loading file: " << path << endl;
		cout << importer.GetErrorString() << endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	const unsigned int numVertices = scene->mMeshes[0]->mNumVertices;
	this->numVertices = numVertices;

	this->vertices = new GLfloat[numVertices * VERTICES_PER_POL];
	for (GLuint i = 0; i < numVertices; ++i) {
		this->vertices[i * VERTICES_PER_POL + 0] = scene->mMeshes[0]->mVertices[i].x;
		this->vertices[i * VERTICES_PER_POL + 1] = scene->mMeshes[0]->mVertices[i].y;
		this->vertices[i * VERTICES_PER_POL + 2] = scene->mMeshes[0]->mVertices[i].z;
	}

	importer.FreeScene();
	return true;
}
