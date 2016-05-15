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

	/*BIND polygon_normals*/
	glGenBuffers(1, &normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numVertices*VERTICES_PER_POL, polygon_normals, GL_STATIC_DRAW);
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

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glVertexAttribPointer(
		1,
		VERTICES_PER_POL,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

bool MeshObject::Import3D(const string& path, bool invert_normals) {
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
	this->numVertices = scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL;

	this->vertices = new GLfloat[scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL * DIMENSIONS];
	this->polygon_normals  = new GLfloat[scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL * DIMENSIONS];
	
	glm::vec3 A, B, C, N, EA, EB, EC, VN;
	for (GLuint i = 0; i < scene->mMeshes[0]->mNumFaces; ++i) {
		if (scene->mMeshes[0]->mFaces[i].mNumIndices != 3) {
			cout << "ERROR: some of the faces are not triangles" << endl;
			getchar();
			exit(-1);
		}

		A = glm::vec3(
			this->vertices[i * 9 + 0] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].x,
			this->vertices[i * 9 + 1] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].y,
			this->vertices[i * 9 + 2] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].z
		);

		B = glm::vec3(
			this->vertices[i * 9 + 3] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].x,
			this->vertices[i * 9 + 4] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].y,
			this->vertices[i * 9 + 5] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].z
		);

		C = glm::vec3(
			this->vertices[i * 9 + 6] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].x,
			this->vertices[i * 9 + 7] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].y,
			this->vertices[i * 9 + 8] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].z
		);

		N = glm::normalize( invert_normals ? glm::cross(A - B, A - C) : glm::cross(A - B, C - A) );

		for (unsigned int j = 0; j < VERTICES_PER_POL; ++j) {
			this->polygon_normals[i * 9 + j * VERTICES_PER_POL + 0] = N.x * 0.5f + 0.5f;
			this->polygon_normals[i * 9 + j * VERTICES_PER_POL + 1] = N.y * 0.5f + 0.5f;
			this->polygon_normals[i * 9 + j * VERTICES_PER_POL + 2] = N.z * 0.5f + 0.5f;
		}
	}

	importer.FreeScene();
	return true;
}
