#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Mesh.h"

class MeshObject : public Object3D {
private:
	Mesh* mesh;

	GLuint vertex_buffer;
	GLuint normal_buffer;
	GLuint uvs_buffer;

	GLuint texture_buffer;

protected:
	bool Import3D(const string& path);
	bool ImportTexture(const string& path);

	GLfloat reflectivity_diffuse;
	GLfloat reflectivity_specular;
	GLfloat reflectivity_ambient;

public:	
	MeshObject();
	MeshObject(aiMesh* meshData);

	void MeshObject::PrintVertices();

	void Init();
	void Update(double dt);

	void DrawDepthMap(GLuint shadow_MID);
	void Draw(GLuint transformID, GLuint textureID, GLuint reflectivityDiffuseID, GLuint reflectivitySpecularID, GLuint reflectivityAmbientID);
};
