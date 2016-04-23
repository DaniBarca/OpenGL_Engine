//Blame @DaniBarca for this

//This is the main class of a project made with this engine

#ifndef WORLD_H
#define WORLD_H

#include "Header.h"

class World
{
	World();
	~World();

public:
	static World* GetInstance();

	void Init();

	void Update(double dt);

	void Draw();

	void OnKeyPress(int key, int scancode, int action, int mods);

	void OnMousePress(int button, int action, int mods);

	void OnMouseMove(double x, double y);
};

#endif