#pragma once

#include "Header.h"
#include "MeshObject.h"

class BasicMesh : public MeshObject
{
	string path;

public:
	BasicMesh(string _path);
	~BasicMesh();

	void Init();
	void Update(double dt);
	void Draw();

};
