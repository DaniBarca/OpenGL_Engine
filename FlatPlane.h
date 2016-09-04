#pragma once

#include "Header.h"
#include "MeshObject.h"

class FlatPlane : public MeshObject
{
public:
	FlatPlane();
	~FlatPlane();

	void Init();
	void Update(double dt);
	void Draw();

};

