#include "MeshManager.h"

MeshManager::MeshManager()
{
	meshList = std::map<string, Mesh*>();
}

MeshManager::~MeshManager()
{
}

MeshManager* MeshManager::GetInstance()
{
	static MeshManager* Instance = new MeshManager();
	return Instance;
}

Mesh * MeshManager::LoadMesh(const string & path, bool invert_normals)
{
	int invert = invert_normals ? -1 : 1;
	
	static std::map<string, Mesh*>::iterator memit;
	if ((memit = meshList.find(path + std::to_string(invert))) != meshList.end()) {
		return memit->second;
	}

	Assimp::Importer importer;

	//Load model with assimp
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	//Check successful result
	if (!scene) {
		cout << "Error while loading file: " << path << endl;
		cout << importer.GetErrorString() << endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	//Get total number of vertices (each vertex is repeated each time it appears in a polygon)
	unsigned int numVertices = scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL;

	GLfloat* vertices = new GLfloat[scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL * DIMENSIONS];
	GLfloat* normals = new GLfloat[scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL * DIMENSIONS];
	GLfloat* uvs = new GLfloat[scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL * 2];

	for (GLuint i = 0; i < scene->mMeshes[0]->mNumFaces; ++i) {
		if (scene->mMeshes[0]->mFaces[i].mNumIndices != 3) {
			cout << "ERROR: some of the faces are not triangles" << endl;
			getchar();
			exit(-1);
		}

		vertices[i * 9 + 0] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].x;
		vertices[i * 9 + 1] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].y;
		vertices[i * 9 + 2] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].z;

		vertices[i * 9 + 3] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].x;
		vertices[i * 9 + 4] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].y;
		vertices[i * 9 + 5] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].z;

		vertices[i * 9 + 6] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].x;
		vertices[i * 9 + 7] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].y;
		vertices[i * 9 + 8] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].z;

		normals[i * 9 + 0] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].x * invert;
		normals[i * 9 + 1] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].y * invert;
		normals[i * 9 + 2] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].z * invert;

		normals[i * 9 + 3] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].x * invert;
		normals[i * 9 + 4] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].y * invert;
		normals[i * 9 + 5] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].z * invert;

		normals[i * 9 + 6] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].x * invert;
		normals[i * 9 + 7] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].y * invert;
		normals[i * 9 + 8] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].z * invert;

		uvs[i * 6 + 0] = scene->mMeshes[0]->uv

	}

	Mesh* m = new Mesh(vertices, normals, numVertices);
	meshList[path + std::to_string(invert)] = m;

	importer.FreeScene();
	return m;
}
