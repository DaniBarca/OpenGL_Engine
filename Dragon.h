#pragma once
#include "Header.h"
#include "MeshObject.h"

class Dragon : public MeshObject
{
public:
	Dragon();
	~Dragon();

	void Init();
	void Update(double dt);
	void Draw();
};

