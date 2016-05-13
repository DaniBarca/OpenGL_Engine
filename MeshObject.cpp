#include "MeshObject.h"

MeshObject::MeshObject() {
	Engine::GetInstance()->LoadShader("shaders/basic_mesh_shader.vertex", "shaders/basic_mesh_shader.fragment", &shaderID);
	matrixID = glGetUniformLocation(shaderID, "PVM");
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

	glUseProgram(shaderID);

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &(Camera::getInstance()->getPV() * *transform)[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(
		0,
		VERTICES_PER_POL,	//size
		GL_FLOAT,			//type
		GL_FALSE,			//normalized
		0,					//stride
		(void*)0			//array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	glDisableVertexAttribArray(0);
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

	size_t vertices_size = 0;
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		vertices_size += scene->mMeshes[i]->mNumFaces * VERTICES_PER_POL * DIMENSIONS;
	}
	
	this->numVertices = scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL;

	this->vertices = new GLfloat[scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL * DIMENSIONS];
	
	unsigned int count = 0;
	//for (GLuint m = 0; m < scene->mNumMeshes; ++m) {
		for (GLuint i = 0; i < scene->mMeshes[0]->mNumFaces; ++i) {
			if (scene->mMeshes[0]->mFaces[i].mNumIndices != 3) {
				cout << "ERROR: some of the faces are not triangles" << endl;
				getchar();
				exit(-1);
			}

			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].x;
			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].y;
			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].z;

			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].x;
			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].y;
			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].z;

			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].x;
			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].y;
			this->vertices[count++] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].z;
		}
	//}

	

	importer.FreeScene();
	return true;
}
