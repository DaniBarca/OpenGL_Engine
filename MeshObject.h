#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Engine.h"
#include "Camera.h"
#include "LightManager.h"

class MeshObject : public Object3D {
	static std::map<string, string> parse_dict;

	GLfloat* vertices;
	GLfloat* vertices_normals;
	unsigned int numVertices;

	GLuint shaderID;
	GLuint matrixID;
	GLuint transformID;
	GLuint lightPosID;
	GLuint lightIntensityID;
	GLuint lightColorID;
	GLuint cameraPositionID;
	GLuint reflectivityDiffuseID;
	GLuint reflectivitySpecularID;
	GLuint reflectivityAmbientID;
	GLuint ambientIntensityID;
	GLuint specularExponentID;

	GLuint vertex_buffer;
	GLuint normal_buffer;

protected:
	bool Import3D(const string& path, bool invert_normals = false);

	GLfloat reflectivity_diffuse;
	GLfloat reflectivity_specular;
	GLfloat reflectivity_ambient;

public:	
	MeshObject();
	MeshObject(aiMesh* meshData);

	void MeshObject::PrintVertices();

	void Init();
	void Update(double dt);
	void Draw();
};
