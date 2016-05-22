#include "LightManager.h"

LightManager::LightManager()
{}

LightManager::~LightManager()
{
	for (unsigned int i = 0; i < lights.size; ++i) {
		delete lights[i];
	}
}

LightManager* LightManager::GetInstance(){
	static LightManager* Instance = new LightManager();
	return Instance;
}

LightManager* LightManager::Push(Light* l) {
	lights.push_back(l);
	return this;
}

Light* LightManager::GetLight(unsigned int pos){
	return lights[pos];
}

void LightManager::Update(float dt) {
	for (unsigned int i = 0; i < lights.size; ++i) {
		lights[i]->Update(dt);
	}
}
