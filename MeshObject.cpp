#include "MeshObject.h"

std::map<string, string> MeshObject::parse_dict;

MeshObject::MeshObject() {
	size_t n_lights = LightManager::GetInstance()->GetNLights();
	parse_dict = std::map<string,string>({
		{ "%N_LIGHTS%", to_string(n_lights > 0 ? n_lights : 1) }
	});

	reflectivity_diffuse = 1.0f;
	reflectivity_specular = 0.5f;
	reflectivity_ambient = 0.2f;

	Engine::GetInstance()->LoadShader(std::vector<std::string>({
		"shaders/phong.vertex",
		"shaders/phong.fragment"
	}), std::vector<GLenum>({
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	}), parse_dict, &shaderID);

	matrixID    = glGetUniformLocation(shaderID, "PV");
	transformID = glGetUniformLocation(shaderID, "M");
	lightPosID  = glGetUniformLocation(shaderID, "light_position");
	lightIntensityID = glGetUniformLocation(shaderID, "light_intensity");
	lightColorID = glGetUniformLocation(shaderID, "light_color");

	cameraPositionID = glGetUniformLocation(shaderID, "camera_position");

	reflectivityDiffuseID  = glGetUniformLocation(shaderID, "reflectivity_diffuse");
	reflectivitySpecularID = glGetUniformLocation(shaderID, "reflectivity_specular");
	reflectivityAmbientID  = glGetUniformLocation(shaderID, "reflectivity_ambient");
	
	ambientIntensityID = glGetUniformLocation(shaderID, "ambient_intensity");
	specularExponentID = glGetUniformLocation(shaderID, "specular_exponent");
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numVertices*VERTICES_PER_POL, vertices_normals, GL_STATIC_DRAW);
}

void MeshObject::Update(double dt){
	Object3D::Update(dt);
}

void MeshObject::Draw(){
	Object3D::Draw();

	glUseProgram(shaderID);

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &(Camera::GetInstance()->getPV())[0][0]);
	glUniformMatrix4fv(transformID, 1, GL_FALSE, &(*transform)[0][0]);

	GLsizei n_lights = (GLsizei)LightManager::GetInstance()->GetNLights();
	glUniform3fv(lightPosID,       n_lights, LightManager::GetInstance()->GetPositions());
	glUniform1fv(lightIntensityID, n_lights, LightManager::GetInstance()->GetIntensities());
	glUniform3fv(lightColorID,     n_lights, LightManager::GetInstance()->GetColors());

	glUniform1fv(reflectivityDiffuseID,  1, &reflectivity_diffuse);
	glUniform1fv(reflectivitySpecularID, 1, &reflectivity_specular);
	glUniform1fv(reflectivityAmbientID,  1, &reflectivity_ambient);

	glUniform1fv(ambientIntensityID, 1, LightManager::GetInstance()->GetAmbientItensity());
	glUniform1fv(specularExponentID, 1, LightManager::GetInstance()->GetSpecularExponent());

	glUniform3fv(cameraPositionID, 1, &Camera::GetInstance()->GetPosition()[0]);

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
	int invert = invert_normals ? -1 : 1;

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

	this->vertices         = new GLfloat[scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL * DIMENSIONS];
	this->vertices_normals = new GLfloat[scene->mMeshes[0]->mNumFaces * VERTICES_PER_POL * DIMENSIONS];
	
	glm::vec3 A, B, C, N, EA, EB, EC, VN;
	for (GLuint i = 0; i < scene->mMeshes[0]->mNumFaces; ++i) {
		if (scene->mMeshes[0]->mFaces[i].mNumIndices != 3) {
			cout << "ERROR: some of the faces are not triangles" << endl;
			getchar();
			exit(-1);
		}

		this->vertices[i * 9 + 0] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].x;
		this->vertices[i * 9 + 1] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].y;
		this->vertices[i * 9 + 2] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].z;

		this->vertices[i * 9 + 3] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].x;
		this->vertices[i * 9 + 4] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].y;
		this->vertices[i * 9 + 5] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].z;

		this->vertices[i * 9 + 6] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].x;
		this->vertices[i * 9 + 7] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].y;
		this->vertices[i * 9 + 8] = scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].z;

		this->vertices_normals[i * 9 + 0] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].x * invert;
		this->vertices_normals[i * 9 + 1] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].y * invert;
		this->vertices_normals[i * 9 + 2] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].z * invert;

		this->vertices_normals[i * 9 + 3] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].x * invert;
		this->vertices_normals[i * 9 + 4] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].y * invert;
		this->vertices_normals[i * 9 + 5] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].z * invert;

		this->vertices_normals[i * 9 + 6] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].x * invert;
		this->vertices_normals[i * 9 + 7] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].y * invert;
		this->vertices_normals[i * 9 + 8] = scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].z * invert;

	}

	importer.FreeScene();
	return true;
}
