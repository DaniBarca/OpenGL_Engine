#include "LightManager.h"

LightManager::LightManager()
{}

LightManager::~LightManager()
{
	for (unsigned int i = 0; i < lights.size(); ++i) {
		delete lights[i];
	}
}

LightManager* LightManager::AllocLights(int n) {
	lights = vector<Light*>();
	lights.resize(n);

	positions = new GLfloat[n * 3];
	intensities = new GLfloat[n];

	return GetInstance();
}

LightManager* LightManager::GetInstance(){
	static LightManager* Instance = new LightManager();
	return Instance;
}

LightManager* LightManager::Push(Light* l) {
	static int count = 0;
	lights[count++] = l;
	return this;
}

Light* LightManager::GetLight(unsigned int pos){
	return lights[pos];
}

size_t LightManager::GetNLights() {
	return lights.size();
}

void LightManager::Update(double dt) {
	for (unsigned int i = 0; i < lights.size(); ++i) {
		lights[i]->Update(dt);
	}

	Compile();
}

void LightManager::Compile() {
	for (unsigned int i = 0; i < lights.size(); ++i) {
		positions[i * 3 + 0] = lights[i]->GetPosition()[0];
		positions[i * 3 + 1] = lights[i]->GetPosition()[1];
		positions[i * 3 + 2] = lights[i]->GetPosition()[2];

		intensities[i] = lights[i]->GetIntensity();
	}
}

GLfloat* LightManager::GetPositions() {
	return positions;
}

GLfloat* LightManager::GetIntensities(){
	return intensities;
}
