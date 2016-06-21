#include "LightManager.h"

LightManager::LightManager()
{
	ambient_intensity = 0.0f;
	specular_exponent = 1.0f;
}

LightManager::~LightManager()
{
	for (unsigned int i = 0; i < lights.size(); ++i) {
		delete lights[i];
	}
}

/*LightManager* LightManager::AllocLights(int n) {
	lights = vector<Light*>();
	lights.resize(n);

	positions = new GLfloat[n * 3];
	intensities = new GLfloat[n];
	colors = new GLfloat[n * 3];

	return GetInstance();
}*/

LightManager* LightManager::GetInstance(){
	static LightManager* Instance = new LightManager();
	return Instance;
}

LightManager* LightManager::Push(Light* l) {
	lights.push_back(l);

	delete[] positions;
	delete[] intensities;
	delete[] colors;

	positions = new GLfloat[lights.size() * 3];
	intensities = new GLfloat[lights.size()];
	colors = new GLfloat[lights.size() * 3];

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
	glm::vec4 aux;
	for (unsigned int i = 0; i < lights.size(); ++i) {
		positions[i * 3 + 0] = lights[i]->GetPosition()[0];
		positions[i * 3 + 1] = lights[i]->GetPosition()[1];
		positions[i * 3 + 2] = lights[i]->GetPosition()[2];

		intensities[i] = lights[i]->GetIntensity();

		aux = clamp(lights[i]->GetColor());
		colors[i * 3 + 0] = aux.r;
		colors[i * 3 + 1] = aux.g;
		colors[i * 3 + 2] = aux.b;
	}
}

GLfloat* LightManager::GetPositions() {
	return positions;
}

GLfloat* LightManager::GetIntensities(){
	return intensities;
}

GLfloat* LightManager::GetColors() {
	return colors;
}

GLfloat * LightManager::GetAmbientItensity()
{
	return &ambient_intensity;
}

GLfloat * LightManager::GetSpecularExponent()
{
	return &specular_exponent;
}

LightManager * LightManager::SetAmbientItensity(float i)
{
	ambient_intensity = i;
	return GetInstance();
}

LightManager * LightManager::SetSpecularExponent(float e)
{
	specular_exponent = e;
	return GetInstance();
}
