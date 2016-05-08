#include "MeshObject.h"

MeshObject::MeshObject() {
	Engine::GetInstance()->LoadShader("shaders/basic_mesh_shader.vertex", "shaders/basic_mesh_shader.fragment", &shaderID);
}

MeshObject::MeshObject(aiMesh* meshData) : MeshObject() {
}

void MeshObject::PrintVertices() {
	for (GLuint i = 0; i < (const unsigned int)(numVertices * 3); ++i) {
		cout << vertices[i];
		if ((i + 1) % 3 == 0)
			cout << endl;
		else
			cout << " -- ";
	}
}

void MeshObject::Init(){
	Object3D::Init();

	/*BIND vertex buffer*/
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numVertices*VERTICES_PER_POL, vertices, GL_STATIC_DRAW);
}

void MeshObject::Update(double dt){
	Object3D::Update(dt);
}

void MeshObject::Draw(){
	Object3D::Draw();
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
