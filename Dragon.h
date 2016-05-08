#pragma once
#include "Header.h"
#include "MeshObject.h"
#include "Import.h"

class Dragon : public MeshObject
{
public:
	Dragon();
	~Dragon();

	void Init();
	void Update(double dt);
	void Draw();
};

