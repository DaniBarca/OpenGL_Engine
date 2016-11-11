#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Mesh.h"

class MeshObject : public Object3D {
private:
	static std::map<string, string> parse_dict;

	Mesh* mesh;

	GLuint shaderID;
	GLuint matrixID;
	GLuint transformID;
	
	GLuint point_positionsID;
	GLuint point_colorsID;
	GLuint point_intensitiesID;
	GLuint point_shininessID;

	GLuint spot_positionsID;
	GLuint spot_colorsID;
	GLuint spot_directionsID;
	GLuint spot_intensitiesID;
	GLuint spot_shininessID;
	GLuint spot_anglesID;

	GLuint directional_positionsID;
	GLuint directional_colorsID;
	GLuint directional_directionsID;
	GLuint directional_intensitiesID;
	GLuint directional_shininessID;

	GLuint cameraPositionID;
	GLuint reflectivityDiffuseID;
	GLuint reflectivitySpecularID;
	GLuint reflectivityAmbientID;

	GLuint ambientColorID;
	GLuint ambientIntensityID;

	GLuint textureID;

	GLuint vertex_buffer;
	GLuint normal_buffer;
	GLuint uvs_buffer;

	GLuint texture_buffer;

	std::vector<std::string> shaderPaths;
	std::vector<GLenum> shaderTypes;

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

	void LoadUniforms();

	void Init();
	void Update(double dt);
	void Draw();
};
