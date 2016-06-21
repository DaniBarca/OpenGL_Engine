#include "MeshObject.h"

std::map<string, string> MeshObject::parse_dict;

MeshObject::MeshObject() {
	size_t n_lights = LightManager::GetInstance()->GetNLights();
	parse_dict = std::map<string,string>({});

	reflectivity_diffuse = 1.0f;
	reflectivity_specular = 0.5f;
	reflectivity_ambient = 0.2f;

	specular_exponent = 50.0f;

	shader_paths = std::vector<std::string>({
		"shaders/phong.vertex",
		"shaders/phong.fragment"
	});

	shader_types = std::vector<GLenum>({
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	});

	Engine::GetInstance()->LoadShader(
		shader_paths, 
		shader_types,
		parse_dict,
		(int)LightManager::GetInstance()->GetNLights(), 
		&shaderID
	);

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
	for (GLuint i = 0; i < (const unsigned int)(mesh->numVertices * 3); ++i) {
		cout << mesh->vertices[i];
		if ((i + 1) % 3 == 0)
			cout << endl;
		else
			cout << " -- ";
	}
}

void MeshObject::Init(){
	Object3D::Init();
	BindConstant();
}

void MeshObject::BindConstant() {
	/*BIND vertex buffer*/
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh->numVertices*VERTICES_PER_POL, mesh->vertices, GL_STATIC_DRAW);

	/*BIND polygon_normals*/
	glGenBuffers(1, &normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh->numVertices*VERTICES_PER_POL, mesh->vertices_normals, GL_STATIC_DRAW);
}

void MeshObject::Update(double dt){
	Object3D::Update(dt);
}

void MeshObject::Draw(){
	static GLuint m;
	Object3D::Draw();
	
	// Reload shader, since the number of lights could have changed
	m = shaderID;
	GLsizei n_lights = (GLsizei)LightManager::GetInstance()->GetNLights();
	Engine::GetInstance()->LoadShader(
		shader_paths,
		shader_types,
		parse_dict,
		n_lights,
		&shaderID
	);

	if (shaderID != m) {
		BindConstant();
	}

	glUseProgram(shaderID);

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &(Camera::GetInstance()->getPV())[0][0]);
	glUniformMatrix4fv(transformID, 1, GL_FALSE, &(*transform)[0][0]);

	glUniform3fv(lightPosID,       n_lights, LightManager::GetInstance()->GetPositions());
	glUniform1fv(lightIntensityID, n_lights, LightManager::GetInstance()->GetIntensities());
	glUniform3fv(lightColorID,     n_lights, LightManager::GetInstance()->GetColors());

	glUniform1fv(reflectivityDiffuseID,  1, &reflectivity_diffuse);
	glUniform1fv(reflectivitySpecularID, 1, &reflectivity_specular);
	glUniform1fv(reflectivityAmbientID,  1, &reflectivity_ambient);

	glUniform1fv(ambientIntensityID, 1, LightManager::GetInstance()->GetAmbientItensity());
	glUniform1fv(specularExponentID, 1, &specular_exponent);

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

	glDrawArrays(GL_TRIANGLES, 0, mesh->numVertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

bool MeshObject::Import3D(const string& path, bool invert_normals) {
	this->mesh = MeshManager::GetInstance()->LoadMesh(path,invert_normals);
	return true;
}
