#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Engine.h"
#include "Camera.h"
#include "LightManager.h"
#include "MeshManager.h"

class MeshObject : public Object3D {
private:
	static std::map<string, string> parse_dict;

	Mesh* mesh;

	GLuint shaderID;
	GLuint matrixID;
	GLuint transformID;
	GLuint lightPosID;
	GLuint lightIntensityID;
	GLuint lightColorID;
	GLuint lightTypeID;
	GLuint cameraPositionID;
	GLuint reflectivityDiffuseID;
	GLuint reflectivitySpecularID;
	GLuint reflectivityAmbientID;
	GLuint ambientIntensityID;
	GLuint specularExponentID;

	GLuint vertex_buffer;
	GLuint normal_buffer;

	std::vector<std::string> shaderPaths;
	std::vector<GLenum> shaderTypes;

protected:
	bool Import3D(const string& path, bool invert_normals = false);

	GLfloat reflectivity_diffuse;
	GLfloat reflectivity_specular;
	GLfloat reflectivity_ambient;

public:	
	MeshObject();
	MeshObject(aiMesh* meshData);

	void MeshObject::PrintVertices();

	void LoadUniforms();

	void Init();
	void Update(double dt);
	void Draw();
};
