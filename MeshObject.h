#pragma once

#include "Header.h"
#include "Object3D.h"
#include "Engine.h"
#include "Camera.h"
#include "Material.h"
#include "LightManager.h"

class MeshObject : public Object3D {
	static std::map<string, string> parse_dict;

	GLfloat* vertices;
	GLfloat* polygon_normals;
	GLfloat* vertices_normals;
	unsigned int numVertices;

	GLuint shaderID;
	GLuint matrixID;
	GLuint transformID;

	GLuint vertex_buffer;
	GLuint normal_buffer;

	map<int, vector<int>> idToPos;
	map<int, glm::vec3> vertexNormal;

	
protected:
	bool Import3D(const string& path, bool invert_normals = false);
	Material material;

public:	
	MeshObject();
	MeshObject(aiMesh* meshData);

	void MeshObject::PrintVertices();

	void Init();
	void Update(double dt);
	void Draw();
};
