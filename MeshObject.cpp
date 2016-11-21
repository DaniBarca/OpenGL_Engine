#include "MeshObject.h"
#include "TextureManager.h"
#include "LightManager.h"
#include "MeshManager.h"
#include "Camera.h"
#include "Engine.h"

std::map<string, string> MeshObject::parse_dict;

MeshObject::MeshObject() {
	parse_dict = std::map<string,string>({});

	reflectivity_diffuse = 1.0f;
	reflectivity_specular = 0.5f;
	reflectivity_ambient = 0.2f;

	shaderPaths = std::vector<std::string>({
		"shaders/phong.vertex",
		"shaders/phong.fragment"
	});

	shaderTypes = std::vector<GLenum>({
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	});

	/*for (int p = 1; p <= DEFAULT_N_POINT_LIGHTS; ++p) {
		for (int s = 1; s <= DEFAULT_N_SPOT_LIGHTS; ++s) {
			for (int d = 1; d <= DEFAULT_N_DIRECTIONAL_LIGHTS; ++d) {
				Engine::GetInstance()->LoadShader(shaderPaths, shaderTypes, p, s, d, parse_dict, &shaderID);
			}
		}
	}*/

	Engine::GetInstance()->LoadShader(shaderPaths, shaderTypes, 
		(int)LightManager::GetInstance()->GetNPointLights(), 
		(int)LightManager::GetInstance()->GetNSpotLights(), 
		(int)LightManager::GetInstance()->GetNDirectionalLights(), 
		parse_dict, &shaderID
	);

	LoadUniforms();
}

MeshObject::MeshObject(aiMesh* meshData) : MeshObject() {
}

void MeshObject::PrintVertices() {
	for (GLuint i = 0; i < (const uint)(mesh->numVertices * 3); ++i) {
		cout << mesh->vertices[i];
		if ((i + 1) % 3 == 0)
			cout << endl;
		else
			cout << " -- ";
	}
}

void MeshObject::LoadUniforms() {
	projectionID = glGetUniformLocation(shaderID, "P");
	viewID       = glGetUniformLocation(shaderID, "V");
	transformID  = glGetUniformLocation(shaderID, "M");

	point_positionsID   = glGetUniformLocation(shaderID, "point_positions");
	point_colorsID      = glGetUniformLocation(shaderID, "point_colors");
	point_intensitiesID = glGetUniformLocation(shaderID, "point_intensities");
	point_shininessID   = glGetUniformLocation(shaderID, "point_shininess");

	spot_positionsID   = glGetUniformLocation(shaderID, "spot_positions");
	spot_colorsID      = glGetUniformLocation(shaderID, "spot_colors");
	spot_directionsID  = glGetUniformLocation(shaderID, "spot_directions");
	spot_intensitiesID = glGetUniformLocation(shaderID, "spot_intensities");
	spot_shininessID   = glGetUniformLocation(shaderID, "spot_shininess");
	spot_anglesID      = glGetUniformLocation(shaderID, "spot_angles");

	directional_positionsID   = glGetUniformLocation(shaderID, "directional_positions");
	directional_colorsID      = glGetUniformLocation(shaderID, "directional_colors");
	directional_directionsID  = glGetUniformLocation(shaderID, "directional_directions");
	directional_intensitiesID = glGetUniformLocation(shaderID, "directional_intensities");
	directional_shininessID   = glGetUniformLocation(shaderID, "directional_shininess");

	cameraPositionID = glGetUniformLocation(shaderID, "camera_position");

	reflectivityDiffuseID  = glGetUniformLocation(shaderID, "reflectivity_diffuse");
	reflectivitySpecularID = glGetUniformLocation(shaderID, "reflectivity_specular");
	reflectivityAmbientID  = glGetUniformLocation(shaderID, "reflectivity_ambient");

	ambientColorID = glGetUniformLocation(shaderID, "ambient_color");
	ambientIntensityID = glGetUniformLocation(shaderID, "ambient_intensity");

	textureID = glGetUniformLocation(shaderID, "albedo");

}

void MeshObject::Init(){
	Object3D::Init();

	/*BIND vertex buffer*/
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh->numVertices*VERTICES_PER_POL, mesh->vertices, GL_STATIC_DRAW);

	/*BIND polygon_normals*/
	glGenBuffers(1, &normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh->numNormals*VERTICES_PER_POL, mesh->normals, GL_STATIC_DRAW);

	/*BIND uvs*/
	glGenBuffers(1, &uvs_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvs_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh->numUvs * 2, mesh->uvs, GL_STATIC_DRAW);
}

void MeshObject::Update(double dt){
	Object3D::Update(dt);
}

void MeshObject::Draw(){
	static int preShaderID;
	Object3D::Draw();

	preShaderID = shaderID;
	Engine::GetInstance()->LoadShader(
		shaderPaths, 
		shaderTypes,
		(int)LightManager::GetInstance()->GetNPointLights(),
		(int)LightManager::GetInstance()->GetNSpotLights(),
		(int)LightManager::GetInstance()->GetNDirectionalLights(),
		parse_dict, 
		&shaderID
	);

	if (preShaderID != shaderID) {
		LoadUniforms();
	}

	glUseProgram(shaderID);

	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &(Camera::GetInstance()->getP())[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &(Camera::GetInstance()->getV())[0][0]);
	glUniformMatrix4fv(transformID, 1, GL_FALSE, &(*transform)[0][0]);

	//Load Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_buffer);
	glUniform1i(textureID, 0);

	GLsizei n_point_lights = (GLsizei)LightManager::GetInstance()->GetNPointLights();
	glUniform3fv(point_positionsID,  n_point_lights, LightManager::GetInstance()->GetPointPositions());
	glUniform3fv(point_colorsID,     n_point_lights, LightManager::GetInstance()->GetPointColors());
	glUniform1fv(point_intensitiesID,n_point_lights, LightManager::GetInstance()->GetPointIntensities());
	glUniform1fv(point_shininessID,  n_point_lights, LightManager::GetInstance()->GetPointShininess());

	GLsizei n_spot_lights = (GLsizei)LightManager::GetInstance()->GetNSpotLights();
	glUniform3fv(spot_positionsID,  n_spot_lights, LightManager::GetInstance()->GetSpotPositions());
	glUniform3fv(spot_colorsID,     n_spot_lights, LightManager::GetInstance()->GetSpotColors());
	glUniform3fv(spot_directionsID, n_spot_lights, LightManager::GetInstance()->GetSpotDirections());
	glUniform1fv(spot_intensitiesID,n_spot_lights, LightManager::GetInstance()->GetSpotIntensities());
	glUniform1fv(spot_shininessID,  n_spot_lights, LightManager::GetInstance()->GetSpotShininess());
	glUniform1fv(spot_anglesID,     n_spot_lights, LightManager::GetInstance()->GetSpotAngles());

	GLsizei n_directional_lights = (GLsizei)LightManager::GetInstance()->GetNDirectionalLights();
 	glUniform3fv(directional_positionsID,  n_directional_lights, LightManager::GetInstance()->GetDirectionalPositions());
	glUniform3fv(directional_colorsID,     n_directional_lights, LightManager::GetInstance()->GetDirectionalColors());
	glUniform3fv(directional_directionsID, n_directional_lights, LightManager::GetInstance()->GetDirectionalDirections());
	glUniform1fv(directional_intensitiesID,n_directional_lights, LightManager::GetInstance()->GetDirectionalIntensities());
	glUniform1fv(directional_shininessID,  n_directional_lights, LightManager::GetInstance()->GetDirectionalShininess());

	glUniform1fv(reflectivityDiffuseID,  1, &reflectivity_diffuse);
	glUniform1fv(reflectivitySpecularID, 1, &reflectivity_specular);
	glUniform1fv(reflectivityAmbientID,  1, &reflectivity_ambient);

	glUniform3fv(ambientColorID, 1, LightManager::GetInstance()->GetAmbientColor());
	glUniform1fv(ambientIntensityID, 1, LightManager::GetInstance()->GetAmbientItensity());

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

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uvs_buffer);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, mesh->numVertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

bool MeshObject::Import3D(const string& path) {
	//this->mesh = MeshManager::GetInstance()->LoadMesh_OBJ(path.c_str());
	this->mesh = MeshManager::GetInstance()->LoadMesh_BIN(path.c_str());
	return true;
}

bool MeshObject::ImportTexture(const string & path)
{
	size_t file_size;
	char* file_data;

	char* fpath = (char*)path.c_str();

	FILE* fp;
	fopen_s(&fp, fpath, "rb");

	string str = "";
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	file_data = new char[file_size];
	fread(file_data, sizeof(char), file_size, fp);

	fclose(fp);

	TextureManager::GetInstance()->LoadImage(&texture_buffer, file_data, (uint)file_size);

	return true;
}
