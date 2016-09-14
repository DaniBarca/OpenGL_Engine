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
		->AllocLights(1, 1, 0)
		->SetAmbientColor(glm::vec3(256.0f,256.0f,256.0f))
		->SetAmbientItensity(0.14f);

	LightManager::GetInstance()->Push(new SpotLight(glm::vec4(256.0f, 100.0f, 0.0f, 0.0f), glm::vec3(1.0f, 5.0f, 0.0f), 0.5f, 0.5f, glm::vec3(0.0f, -1.0f, 0.0f) , 0.1f)); 
	LightManager::GetInstance()->Push(new Light(glm::vec4(256.0f, 256.0f, 0.0f, 0.0f), glm::vec3(10.0f,0.0f,0.0f),10.0f, 0.5f));

	//teapot = new Teapot();
	dragon = new Dragon();
	dragon2 = new Dragon();
	dragon3 = new Dragon();

	dragon2->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	dragon3->SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));

	//teapot->Init();
	dragon->Init();
	dragon2->Init();
	dragon3->Init();

	plane = new FlatPlane();
	plane->Init();

	//plane->SetRotation(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	plane->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	Camera::GetInstance();
}

void World::Update(double dt) {
	LightManager::GetInstance()->Update(dt);

	//teapot->Update(dt);
	dragon->Update(dt);
	//dragon2->Update(dt);
	//dragon3->Update(dt);

	plane->Update(dt);
}

void World::Draw() {
	//teapot->Draw();
	//dragon->Draw();
	//dragon2->Draw();
	//dragon3->Draw();

	plane->Draw();
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
			Camera::GetInstance()->Closer();
			break;
		case GLFW_KEY_LEFT:
			Camera::GetInstance()->Beyond();
			break;
		case GLFW_KEY_L:
			if (action == GLFW_RELEASE) {
				LightManager::GetInstance()->Push(new Light(glm::vec4(0.0f, 0.0f, 256.0f, 0.0f), glm::vec3(-10.0f, -2.0f + 10.0f, 0.0f), 0.3f));
			}
			break;
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
