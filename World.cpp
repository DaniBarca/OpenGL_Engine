#include "World.h"

World::World()
{
	pressed_keys = 0;
	clicking = false;
}

World::~World()
{}

World* World::GetInstance() {
	static World* Instance = new World();
	return Instance;
}

void World::Init() {
	teapot = new Teapot();
	dragon = new Dragon();

	teapot->Init();
	dragon->Init();

	glm::translate(*teapot->Transform(), V_LEFT * 100.0f);
	glm::translate(*dragon->Transform(), V_RIGHT * 100.0f);

	Camera::getInstance();
}

void World::Update(double dt) {
	teapot->Update(dt);
	dragon->Update(dt);
}

void World::Draw() {
	teapot->Draw();
	dragon->Draw();
}

void World::OnKeyPress(int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
		++pressed_keys;
	if (action == GLFW_RELEASE)
		--pressed_keys;

	switch (key) {
		case GLFW_KEY_UP:
			Camera::getInstance()->ZoomIN();
			break;
		case GLFW_KEY_DOWN:
			Camera::getInstance()->ZoomOUT();
			break;
		case GLFW_KEY_RIGHT:
			Camera::getInstance()->Beyond();
			break;
		case GLFW_KEY_LEFT:
			Camera::getInstance()->Closer();
			break;
	}
}

void World::OnMousePress(int button, int action, int mods) {
	clicking = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS;
}

void World::OnMouseMove(double x, double y) {
	if (clicking) {
		Camera::getInstance()->Orbit(-x * 2.0f * PI * I_SCREEN_WIDTH, -PI * 0.5f + y * PI * I_SCREEN_HEIGHT);
	}
}
