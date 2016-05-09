#pragma once
#include "Header.h"
#include "MeshObject.h"

class Teapot : public MeshObject
{
public:
	Teapot();
	~Teapot();

	void Init();
	void Update(double dt);
	void Draw();
};

