//Blame @DaniBarca for this

//This is the main class of a project made with this engine

#pragma once

#include "Header.h"
#include "MeshObject.h"
#include "Camera.h"

#include "Teapot.h"
#include "Dragon.h"

#include "Color.h"
#include "LightManager.h"

class World
{
	World();
	~World();

	aiScene asScene;
	Teapot* teapot;
	Dragon* dragon;

	unsigned int pressed_keys;
	bool clicking;

public:
	static World* GetInstance();

	void Init();

	void Update(double dt);

	void Draw();

	void OnKeyPress(int key, int scancode, int action, int mods);

	void OnMousePress(int button, int action, int mods);

	void OnMouseMove(double x, double y);
};
