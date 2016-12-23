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
		->AllocLights(0, 0, 1)
		->SetAmbientColor(glm::vec3(256.0f,256.0f,256.0f))
		->SetAmbientItensity(0.0f);

	//LightManager::GetInstance()->Push(
	//	new SpotLight(
	//		glm::vec4(256.0f, 256.0f, 256.0f, 0.0f), 
	//		glm::vec3(0.0f, 3.0f, 0.0f),
	//		10.0f, 
	//		0.3f, 
	//		glm::vec3(0.0f, -1.0f, 0.0f), 
	//		0.15f,
	//		0.18f
	//	)
	//);
    //
	//LightManager::GetInstance()->Push(
	//	new Light(
	//		glm::vec4(256.0f, 256.0f, 256.0f, 0.0f), 
	//		glm::vec3(-10.0f,3.0f,0.0f),
	//		10.0f, 
	//		0.3f
	//	)
	//);

	LightManager::GetInstance()->Push(
		new DirectionalLight(
			glm::vec4(256.0f,256.0f,256.0f, 0.0f),
			glm::vec3(0.0f,20.0f,0.0f),
			10.0f,
			0.5f,
			glm::vec3(0.0f,-1.0f,0.0f)
		)
	);

	items = std::vector<MeshObject*>();

	items.push_back(new BasicMesh("models/suzanne.obj.bin", "models/monaco.bmp"));
	items.push_back(new BasicMesh("models/BOLLOFLAT.obj.bin", "models/monaco.bmp"));

	for (uint i = 0; i < items.size(); ++i) {
		items[i]->Init();
	}

	Camera::GetInstance(); 
}

void World::Update(double dt) {
	//LightManager::GetInstance()->GetDirectionalLights()[0]->Transform = *LightManager::GetInstance()->GetDirectionalLights()[0]->Transform;

	*LightManager::GetInstance()->GetDirectionalLights()[0]->Transform() = glm::rotate((float)(dt), glm::vec3(1, 0, 0))*(*LightManager::GetInstance()->GetDirectionalLights()[0]->Transform());


	LightManager::GetInstance()->Update(dt);

	for (uint i = 0; i < items.size(); ++i) {
		items[i]->Update(dt);
	}
}

void World::Draw() {
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//LightManager::GetInstance()->GenerateShadows(items);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for (uint i = 0; i < items.size(); ++i) {
		items[i]->Draw();
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
