#include "MeshObject.h"
#include "TextureManager.h"
#include "LightManager.h"
#include "MeshManager.h"
#include "Camera.h"
#include "Engine.h"

MeshObject::MeshObject() {
	reflectivity_diffuse = 1.0f;
	reflectivity_specular = 0.5f;
	reflectivity_ambient = 0.2f;


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
}

void MeshObject::DrawDepthMap(GLuint shadow_MID) {
	glUniformMatrix4fv(shadow_MID, 1, GL_FALSE, &(*transform)[0][0]);

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

	glDrawArrays(GL_TRIANGLES, 0, mesh->numVertices);
	 
	glDisableVertexAttribArray(0);
}

void MeshObject::Draw(GLuint transformID, GLuint textureID, GLuint reflectivityDiffuseID, GLuint reflectivitySpecularID, GLuint reflectivityAmbientID){

	//Load Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_buffer);
	glUniform1i(textureID, 0);
	
	glUniformMatrix4fv(transformID, 1, GL_FALSE, &(*transform)[0][0]);
	glUniform1fv(reflectivityDiffuseID,  1, &reflectivity_diffuse);
	glUniform1fv(reflectivitySpecularID, 1, &reflectivity_specular);
	glUniform1fv(reflectivityAmbientID,  1, &reflectivity_ambient);

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
	glDisableVertexAttribArray(2);
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
