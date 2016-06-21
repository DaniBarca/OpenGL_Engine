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
	LightManager::GetInstance()
		//		->AllocLights(2)
		->SetAmbientItensity(0.0f);
	//	->SetSpecularExponent(30.0f);

	LightManager::GetInstance()->Push(new RotatingLight(glm::vec4(256.0f, 256.0f, 256.0f, 0.0f), glm::vec3(5.0f,5.0f,5.0f),0.9f));
	//LightManager::GetInstance()->Push(new Light(glm::vec4(256.0f, 0.0f, 0.0f, 0.0f), glm::vec3(-10.0f, -10.0f, -10.0f), 0.4f));

	int n = 30;
	dragons = std::vector<Dragon*>();

	for (int i = 0; i < n; ++i) {
		dragons.push_back(new Dragon());
		dragons[i]->SetPosition(glm::vec3(i - (int)(n * 0.5), 0.0f, 0.0f));
		dragons[i]->Init();
	}

	//teapot = new Teapot();
	//teapot->Init();

	Camera::GetInstance();
}

void World::Update(double dt) {
	LightManager::GetInstance()->Update(dt);

	//teapot->Update(dt);
	
	for (int i = 0; i < dragons.size(); ++i) {
		dragons[i]->Update(dt);
	}
}

void World::Draw() {
	//teapot->Draw();
	for (int i = 0; i < dragons.size(); ++i) {
		dragons[i]->Draw();
	}
}

void World::OnKeyPress(int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
		++pressed_keys;
	if (action == GLFW_RELEASE)
		--pressed_keys;

	switch (key) {
		case GLFW_KEY_UP:
			Camera::GetInstance()->ZoomIN();
			break;
		case GLFW_KEY_DOWN:
			Camera::GetInstance()->ZoomOUT();
			break;
		case GLFW_KEY_RIGHT:
			Camera::GetInstance()->Beyond();
			break;
		case GLFW_KEY_LEFT:
			Camera::GetInstance()->Closer();
			break;
		case GLFW_KEY_L:
			LightManager::GetInstance()->Push(new Light(glm::vec4(0.0f, 0.0f, 255.0f, 1.0f), glm::vec3(0.0f, 0.0f, -10.0f), 0.7f));
	}
}

void World::OnMousePress(int button, int action, int mods) {
	clicking = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS;
}

void World::OnMouseMove(double x, double y) {
	if (clicking) {
		Camera::GetInstance()->Orbit(-x * 2.0f * PI * I_SCREEN_WIDTH, -PI * 0.5f + y * PI * I_SCREEN_HEIGHT);
	}
}
