//Blame @DaniBarca for this

//This is the main class of a project made with this engine

#pragma once

#include "Header.h"
#include "Import.h"
#include "MeshObject.h"

class World
{
	World();
	~World();

	aiScene asScene;
	MeshObject* mo;

public:
	static World* GetInstance();

	void Init();

	void Update(double dt);

	void Draw();

	void OnKeyPress(int key, int scancode, int action, int mods);

	void OnMousePress(int button, int action, int mods);

	void OnMouseMove(double x, double y);
};
