#include "Import.h"

bool Import3D(const string& path, MeshObject*& meshes) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace		|
		aiProcess_Triangulate			|
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (!scene) {
		cout << "Error while loading file: " << path << endl;
		cout << importer.GetErrorString() << endl;
		getchar();
		exit(EXIT_FAILURE);
	}
	
	meshes = new MeshObject[1];
	
	const unsigned int numVertices = scene->mMeshes[0]->mNumVertices;
	meshes[0].numVertices = numVertices;

	meshes[0].vertexBuffer = new GLfloat[numVertices * VERTICES_PER_POL];	
	for (GLuint i = 0; i < numVertices; ++i) {
		meshes[0].vertexBuffer[i * VERTICES_PER_POL + 0] = scene->mMeshes[0]->mVertices[i].x;
		meshes[0].vertexBuffer[i * VERTICES_PER_POL + 1] = scene->mMeshes[0]->mVertices[i].y;
		meshes[0].vertexBuffer[i * VERTICES_PER_POL + 2] = scene->mMeshes[0]->mVertices[i].z;
	}

	importer.FreeScene();
	return true;
}
