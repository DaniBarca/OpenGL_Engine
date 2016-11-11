#pragma once

#include "Header.h"
#include "MeshObject.h"

class BasicMesh : public MeshObject
{
	string path, texture_path;

public:
	BasicMesh(string _path, string _texture_path);
	~BasicMesh();

	void Init();
	void Update(double dt);
	void Draw();

};
