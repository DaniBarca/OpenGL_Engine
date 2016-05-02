#include "World.h"

World::World()
{}

World::~World()
{}

World* World::GetInstance() {
	static World* Instance = new World();
	return Instance;
}

void World::Init() {
	/*TESTING IMPORT WITH ASSIMP*/
	cout << "Loading teapot" << endl;
	Import3D("models/teapot.obj", mo);
	cout << "Finished teapot read" << endl;

	for (GLuint i = 0; i < mo[0].numVertices * 3; ++i) {
		std::cout << mo[0].vertexBuffer[i] << " -- ";
		if ((i + 1) % 3 == 0)
			std::cout << endl;
	}

	cout << "Dafuck" << endl;
}

void World::Update(double dt) {
}

void World::Draw() {
}

void World::OnKeyPress(int key, int scancode, int action, int mods) {
}

void World::OnMousePress(int button, int action, int mods) {
}

void World::OnMouseMove(double x, double y) {
}
